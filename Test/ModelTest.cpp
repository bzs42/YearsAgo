#include "ModelTest.h"

#include <QTest>

#include "Model.h"

void ModelTest::initTestCase()
{

}

void ModelTest::init()
{

}

void ModelTest::cleanupTestCase()
{

}

void ModelTest::testSearch()
{
    Model model;
    model.setImageFolder("d:\\GitHub\\Beheleke\\YearsAgo\\Test\\Fixture");
    model.setDate(QDate(2020,2,9));
}

QTEST_APPLESS_MAIN(ModelTest)
