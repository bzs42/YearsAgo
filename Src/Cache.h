#ifndef CACHE_H
#define CACHE_H

#include <QDate>
#include <QMap>
#include <QObject>
#include <QString>

class Cache : public QObject
{
    Q_OBJECT
    
public:
    Cache(const QString filePath, QObject* parent = nullptr);
    ~Cache();
    
    QMap<QString, QVector<QString>> getImages(QDate date);
    
    void clear();
    void addEntry(QString path, QDate date);
    
protected:
    void load();
    void save();    

private:
    std::vector<std::pair<QString, QDate>> m_images;
    QString m_cacheFile;
};

#endif // CACHE_H
