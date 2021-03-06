#ifndef MODEL_H
#define MODEL_H

#include <QDate>
#include <QImage>
#include <QObject>

class Model : public QObject
{
    Q_OBJECT

public:
    Model();
    ~Model();

    QString imageFolder() const;
    void setImageFolder(const QString& value);
    QImage imageYearsAgo() const;
    int yearsAgo() const;
    QDate date() const;

public slots:
    void setDate(const QDate& value);
    void setYearsAgo(int value);

signals:
    void imageYearsAgoChanged(const QImage& value);
    void matchCountChanged(int);
    void dateChanged(const QDate& value);

private:
    void search();

private:
    int m_yearsAgo;
    QDate m_date;
    QString m_imageFolder;
    QImage m_imageYearsAgo;
    QVector<QString> m_sameDateMatches;
};

#endif // MODEL_H
