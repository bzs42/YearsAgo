#include "SearchAlgorithm.h"

#include <QDebug>
#include <QDirIterator>
#include <QImageReader>

SearchAlgorithm::SearchAlgorithm(const QString& folder, const QDate& date)
    : m_folder(folder)
    , m_date(date)
{

}

void SearchAlgorithm::search()
{
    m_images.clear();
    QString year = QString::number(m_date.year());

    QDirIterator it(m_folder, {"*.png", "*.jpg"}, QDir::Files, QDirIterator::Subdirectories);

    int imageCount = 0;
    int imagesFailed = 0;

    while(it.hasNext())
    {
        it.next();

        imageCount++;

        QDate imageDate = dateFromFileName(it.fileInfo().absolutePath(), it.fileName());
        if (imageDate.isNull()) {
            imagesFailed++;
            qDebug() << it.fileInfo().absolutePath() << it.fileName() << "invalid date, skipped";
            continue;
        }

        if((imageDate.day() == m_date.day()) && (imageDate.month() == m_date.month()))
        {
            auto& images = m_images[QString::number(imageDate.year())];
            images.append(it.filePath());
        }
    }

    qDebug() << "images found" << imageCount;
    qDebug() << "images no date match" << imagesFailed;

    QMap<QString, QVector<QString>>::const_iterator i = m_images.constBegin();
    while(i != m_images.constEnd())
    {
        qDebug() << i.key() << ":" << i.value().size();
        ++i;
    }
}

QMap<QString, QVector<QString>> SearchAlgorithm::getImages()
{
    return m_images;
}

QDate SearchAlgorithm::dateFromFileName(const QString& dir, const QString& name)
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

    // TODO: ambiguous, can be 19 or 20 or whatever
    QRegularExpression re2(R"(^(\d\d)(\d\d)(\d\d)_)");
    match = re2.match(name);

    if (match.hasMatch()) {
        QDate imageDate =
            QDate(
                match.captured(1).toInt() + 2000,
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

