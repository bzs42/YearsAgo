#include "CacheTest.h"

#include <Cache.h>

#include <QTest>

void CacheTest::testSave()
{
    Cache cache("cache.txt");
    cache.addEntry("D:\\test\\test.png", QDate::currentDate());
}

QTEST_APPLESS_MAIN(CacheTest)