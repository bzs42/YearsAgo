#ifndef SEARCHTHREAD_H
#define SEARCHTHREAD_H

#include <QThread>
#include <QObject>

class SearchThread : public QThread
{
    Q_OBJECT

    // QThread interface
protected:
    void run() override;

signals:
    void resultReady();

};

#endif // SEARCHTHREAD_H
