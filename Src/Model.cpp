#include "Model.h"

#include <QDebug>
#include <QDirIterator>
#include <QImage>
#include <QImageReader>
#include <QRegularExpression>
#include <QSettings>

Model::Model()
{
    // TODO: load settings
    m_imageOneYearAgo = QImage(":/DummyImage.png");

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

QImage Model::imageOneYearAgo() const
{
    return m_imageOneYearAgo;
}

void Model::setDate(const QDate& value)
{
    if (value == m_date) {
        return;
    }
    m_date = value;
    search();
}

void Model::search()
{
    if (m_date.isNull()) {
        return;
    }
    if (m_imageFolder.isEmpty()) {
        return;
    }

    QDirIterator it(m_imageFolder, {"*.png", "*.jpg"}, QDir::Files, QDirIterator::Subdirectories);
    QRegularExpression re(R"(^(\d\d\d\d)(\d\d)(\d\d)_)");
    QDate yearAgo = m_date.addYears(-1);
    QVector<QString> sameDate;
    QVector<QString> nearest;

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
            sameDate.append(it.filePath());

            if (sameDate.size() > 1) {
                continue;
            }

            // need image reader to handle jpg orientation, QImage doesn't do it
            QImageReader reader(it.filePath());
            reader.setAutoTransform(true);
            m_imageOneYearAgo = reader.read();
            Q_ASSERT(!m_imageOneYearAgo.isNull());
            emit imageOneYearAgoChanged(m_imageOneYearAgo);
            qDebug() << "image found";

            continue;
        }

        if (days > -15 && days < 15) {
            nearest.append(it.fileName());
        }
    }

    qDebug() << "same date found" << sameDate.size();
    qDebug() << "nearest found" << nearest.size();
}
