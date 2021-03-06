#include "Model.h"

#include <QImage>

Model::Model()
{
    // TODO: load settings
    m_imageOneYearAgo = QImage(":/DummyImage.png");
}

Model::~Model()
{
    // TODO: save settings
}

QString Model::imageFolder() const
{
    return m_imageFolder;
}

void Model::setImageFolder(const QString& value)
{
    if (value == m_imageFolder) {
        return;
    }
    m_imageFolder = value;
}

QImage Model::imageOneYearAgo() const
{
    return m_imageOneYearAgo;
}

void Model::setDate(QDate value)
{
    if (value == m_date) {
        return;
    }
    m_date = value;
}
