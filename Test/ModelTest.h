#ifndef MODELTEST_H
#define MODELTEST_H

#include <QObject>

class ModelTest : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void init();
    void cleanupTestCase();

    void testSearch();

};

#endif // MODELTEST_H
