#include "Model.h"

#include <QDebug>
#include <QDirIterator>
#include <QImage>
#include <QImageReader>
#include <QRegularExpression>
#include <QSettings>

Model::Model()
    : m_yearsAgo(1)
{
    m_imageYearsAgo = QImage(":/DummyImage.png");

    QSettings settings;
    m_imageFolder = settings.value("imageFolder", QString()).toString();
}

Model::~Model()
{
    QSettings settings;
    settings.setValue("imageFolder", m_imageFolder);
}

QString Model::imageFolder() const
{
    return m_imageFolder;
}

void Model::setImageFolder(const QString& value)
{
    if (value == m_imageFolder) {
        return;
    }
    m_imageFolder = value;
    search();
}

QImage Model::imageYearsAgo(int matchNumber) const
{
    if(matchNumber == 0) {
        return m_imageYearsAgo;
    }

    if(matchNumber > 0 && matchNumber < m_sameDateMatches.size()) {
        QImageReader reader(m_sameDateMatches[matchNumber]);
        reader.setAutoTransform(true);
        QImage image = reader.read();
        Q_ASSERT(!image.isNull());
        return image;
    }

    return QImage();
}

QDate Model::date() const
{
    return m_date;
}

void Model::setDate(const QDate& value)
{
    if (value == m_date) {
        return;
    }
    m_date = value;
    emit dateChanged(m_date);
    search();
}

int Model::yearsAgo() const
{
    return m_yearsAgo;
}

void Model::setYearsAgo(int value)
{
    if( m_yearsAgo == value) {
        return;
    }
    m_yearsAgo = value;
    search();
}

void Model::search()
{
    // TODO [ab]: start as a separate thread
    // TODO [ab]: add more regular expressions

    if (m_date.isNull()) {
        return;
    }
    if (m_imageFolder.isEmpty()) {
        return;
    }

    QDirIterator it(m_imageFolder, {"*.png", "*.jpg"}, QDir::Files, QDirIterator::Subdirectories);
    QRegularExpression re(R"(^(\d\d\d\d)(\d\d)(\d\d)_)");
    QDate yearAgo = m_date.addYears(-m_yearsAgo);
    m_sameDateMatches.clear();

    while (it.hasNext())
    {
        it.next();
        qDebug() << it.filePath();

        QRegularExpressionMatch match = re.match(it.fileName());

        if (!match.hasMatch()) {
            qDebug() << "no match";
            continue;
        }

        QString year = match.captured(1);
        QString month = match.captured(2);
        QString day = match.captured(3);

        QDate imageDate = QDate(year.toInt(), month.toInt(), day.toInt());
        if (imageDate.isNull()) {
            qDebug() << "invalid date, skipped" << year << month << day;
            continue;
        }

        qint64 days = yearAgo.daysTo(imageDate);
        qDebug() << imageDate << days;

        if (days==0) {
            m_sameDateMatches.append(it.filePath());

            if (m_sameDateMatches.size() > 1) {
                continue;
            }

            // need image reader to handle jpg orientation, QImage doesn't do it
            QImageReader reader(it.filePath());
            reader.setAutoTransform(true);
            m_imageYearsAgo = reader.read();
            Q_ASSERT(!m_imageYearsAgo.isNull());
            emit imageYearsAgoChanged(m_imageYearsAgo);
            qDebug() << "image found";

            continue;
        }
    }

    qDebug() << "same date found" << m_sameDateMatches.size();
    emit matchCountChanged(m_sameDateMatches.size());
}


