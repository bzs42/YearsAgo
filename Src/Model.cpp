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
    // TODO [ab]: retrieve date from filepath, not only name

    if (m_date.isNull()) {
        return;
    }
    if (m_imageFolder.isEmpty()) {
        return;
    }

    QDirIterator it(m_imageFolder, {"*.png", "*.jpg"}, QDir::Files, QDirIterator::Subdirectories);

    QDate yearAgo = m_date.addYears(-m_yearsAgo);
    m_sameDateMatches.clear();

    int images = 0;
    int imagesFailed = 0;

    while (it.hasNext())
    {
        it.next();

        images++;

        QDate imageDate = dateFromFileName(it.fileInfo().absolutePath(), it.fileName());
        if (imageDate.isNull()) {
            imagesFailed++;
            qDebug() << it.fileInfo().absolutePath() << it.fileName() << "invalid date, skipped";
            continue;
        }

        qint64 days = yearAgo.daysTo(imageDate);
        //qDebug() << imageDate << days;

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
    qDebug() << "images found" << images;
    qDebug() << "images no date match" << imagesFailed;

    emit matchCountChanged(m_sameDateMatches.size());
}

QDate Model::dateFromFileName(const QString& dir, const QString& name)
{
    QRegularExpression re1(R"((\d\d\d\d)(\d\d)(\d\d))");
    QRegularExpressionMatch match = re1.match(name);

    if (match.hasMatch()) {
        QDate imageDate =
            QDate(
                match.captured(1).toInt(),
                match.captured(2).toInt(),
                match.captured(3).toInt());
        if(!imageDate.isNull()) {
            return imageDate;
        }
    }

    QRegularExpression re2(R"(^(\d\d)(\d\d)(\d\d)_)");
    match = re2.match(name);

    if (match.hasMatch()) {
        QDate imageDate =
            QDate(
                match.captured(1).toInt(),
                match.captured(2).toInt(),
                match.captured(3).toInt());
        if(!imageDate.isNull()) {
            return imageDate;
        }
    }

    QRegularExpression re3(R"((\d\d\d\d)-(\d\d)-(\d\d))");
    match = re3.match(name);

    if (match.hasMatch()) {
        QDate imageDate =
            QDate(
                match.captured(1).toInt(),
                match.captured(2).toInt(),
                match.captured(3).toInt());
        if(!imageDate.isNull()) {
            return imageDate;
        }
    }

    QRegularExpression re4(R"((\d\d).(\d\d).(\d\d\d\d))");
    match = re4.match(dir);

    if (match.hasMatch()) {
        QDate imageDate =
            QDate(
                match.captured(3).toInt(),
                match.captured(2).toInt(),
                match.captured(1).toInt());
        if(!imageDate.isNull()) {
            return imageDate;
        }
    }

    // dir

    QRegularExpression re5(R"((\d\d\d\d)-(\d\d)-(\d\d))");
    match = re5.match(dir);

    if (match.hasMatch()) {
        QDate imageDate =
            QDate(
                match.captured(1).toInt(),
                match.captured(2).toInt(),
                match.captured(3).toInt());
        if(!imageDate.isNull()) {
            return imageDate;
        }
    }

    QRegularExpression re6(R"((\d\d).(\d\d).(\d\d\d\d))");
    match = re6.match(dir);

    if (match.hasMatch()) {
        QDate imageDate =
            QDate(
                match.captured(3).toInt(),
                match.captured(2).toInt(),
                match.captured(1).toInt());
        if(!imageDate.isNull()) {
            return imageDate;
        }
    }

    return QDate();
}


