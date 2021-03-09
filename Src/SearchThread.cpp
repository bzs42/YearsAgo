#include "SearchThread.h"

#include <SearchAlgorithm.h>

SearchThread::SearchThread(const QString& folder, const QDate& date, QObject* parent)
    : QThread(parent)
    , m_folder(folder)
    , m_date(date)
{

}

void SearchThread::run()
{
    SearchAlgorithm algorithm(m_folder, m_date);
    QVector<QString> sameDateMatches = algorithm.search();

    emit searchResultReady(sameDateMatches);
}
