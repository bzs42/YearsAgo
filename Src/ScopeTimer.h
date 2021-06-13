#ifndef SCOPETIMER_H
#define SCOPETIMER_H

#include <QDebug>
#include <QElapsedTimer>
#include <QString>

class ScopeTimer
{
    
public:
    explicit ScopeTimer(const QString& name)
        : m_name(name)
    {
        m_timer.start();
    }
    
    ~ScopeTimer()
    {
        qDebug() << m_name << m_timer.elapsed() << "ms";
    }
    
    ScopeTimer() = delete;
    ScopeTimer(const ScopeTimer&) = delete;

protected:
    QElapsedTimer m_timer;
    QString m_name;
};

#endif // SCOPETIMER_H
