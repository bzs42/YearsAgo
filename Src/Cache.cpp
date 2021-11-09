#include "Cache.h"
#include <QFile>
#include <QStandardPaths>
#include <QTextStream>

Cache::Cache(const QString filePath, QObject* parent)
    : m_cacheFile(filePath)
{
    load();
}

Cache::~Cache()
{
    save();
}

QMap<QString, QVector<QString> > Cache::getImages(QDate date)
{
    QMap<QString, QVector<QString>> matches;
    for(const auto& image : m_images)
    {
        const auto imagePath = image.first;
        const auto imageDate = image.second;
        if(date.month() == imageDate.month() 
           && date.day() == imageDate.day())
        {
            auto &imagesOfYear = matches[QString::number(imageDate.year())];
            imagesOfYear.append(imagePath);
        }
    }
    return matches;
}

void Cache::clear()
{
    m_images.clear();
}

void Cache::addEntry(QString path, QDate date)
{
    m_images.push_back(std::make_pair(path, date));
}

void Cache::load()
{
    
}

void Cache::save()
{
    QString path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QFile file(path + "/cache.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        // TODO: message
        assert(false);
    }
    QTextStream out(&file);
    for (const auto& image : m_images)
    {
        out << image.first << " " << image.second.toString("YYYY-MM-dd") << "\n";
    }
}
