#ifndef SEARCHALGORITHM_H
#define SEARCHALGORITHM_H

#include <QDate>
#include <QMap>
#include <QString>
#include <QVector>

class SearchAlgorithm
{
public:
    SearchAlgorithm() = delete;
    SearchAlgorithm(const QString& folder, const QDate& date);
    void search();
    // TODO: reference and const?
    QMap<QString, QVector<QString> > getImages();

private:
    QDate dateFromFileName(const QString& dir, const QString& name);

private:
    QString m_folder;
    QDate m_date;
    QMap<QString, QVector<QString>> m_images; // year, filelist
};

#endif // SEARCHALGORITHM_H
