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

    QImage imageOneYearAgo() const;

public slots:
    void setDate(const QDate& value);

signals:
    void imageOneYearAgoChanged(const QImage& value);

private:
    void search();

private:
    QDate m_date;
    QString m_imageFolder;
    QImage m_imageOneYearAgo;

};

#endif // MODEL_H
