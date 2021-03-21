#ifndef MODEL_H
#define MODEL_H

#include <QDate>
#include <QImage>
#include <QMap>
#include <QObject>

class Model : public QObject
{
    Q_OBJECT

public:
    Model();
    ~Model();

    QString imageFolder() const;
    void setImageFolder(const QString& value);
    // return the matched image with count, else invalid image
    QImage imageYearsAgo(int matchNumber = 0) const;
    int yearsAgo() const;
    QDate date() const;

public slots:
    void setDate(const QDate& value);
    void setYearsAgo(int value);
    void onSearchResultReady(QMap<QString, QVector<QString>> value);

signals:
    // emmited during search
    void imageYearsAgoChanged(const QImage& value);
    // emitted after search
    void matchCountChanged(int);
    // emmited when date is changed
    void dateChanged(const QDate& value);
    void searchStarted();
    void searchFinished();

private:
    void search();
    QDate dateFromFileName(const QString& dir, const QString& name);
    int getImageCount(int year) const;
    QImage getImage(int year, int index) const;

private:
    int m_yearsAgo;
    bool m_isSearching;
    QDate m_date;
    QString m_imageFolder;
    QImage m_imageYearsAgo;
    QMap<QString, QVector<QString>> m_sameDateMatches;
};

#endif // MODEL_H
