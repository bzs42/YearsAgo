#ifndef SEARCHALGORITHM_H
#define SEARCHALGORITHM_H

#include <QDate>
#include <QString>
#include <QVector>

class SearchAlgorithm
{
public:
    SearchAlgorithm() = delete;
    SearchAlgorithm(const QString& folder, const QDate& date);
    QVector<QString> search();

private:
    QDate dateFromFileName(const QString& dir, const QString& name);

private:
    QString m_folder;
    QDate m_date;
};

#endif // SEARCHALGORITHM_H
