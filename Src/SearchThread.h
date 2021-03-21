#ifndef SEARCHTHREAD_H
#define SEARCHTHREAD_H

#include <QThread>
#include <QObject>
#include <QString>
#include <QDate>
#include <QMap>

class SearchThread : public QThread
{
    Q_OBJECT

public:
    SearchThread() = delete;
    SearchThread(const QString& folder, const QDate& date, QObject* parent = nullptr);

    // QThread interface
protected:
    void run() override;

signals:
    void searchResultReady(QMap<QString, QVector<QString>> value);

private:
    QString m_folder;
    QDate m_date;

};

#endif // SEARCHTHREAD_H
