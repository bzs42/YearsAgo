#include "Model.h"

#include <QDebug>
#include <QDirIterator>
#include <QImage>
#include <QImageReader>
#include <QRegularExpression>
#include <QSettings>

#include "SearchThread.h"
#include "SearchAlgorithm.h"

Model::Model()
    : m_yearsAgo(1)
{
    m_imageYearsAgo = QImage(":/DummyImage.png");

    QSettings settings;
    m_imageFolder = settings.value("imageFolder", QString()).toString();
}

Model::~Model()
{
    QSettings settings;
    settings.setValue("imageFolder", m_imageFolder);
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
    search();
}

QImage Model::imageYearsAgo(int matchNumber) const
{
    if(matchNumber == 0) {
        return m_imageYearsAgo;
    }

    if(matchNumber > 0 && matchNumber < m_sameDateMatches.size()) {
        QImageReader reader(m_sameDateMatches[matchNumber]);
        reader.setAutoTransform(true);
        QImage image = reader.read();
        Q_ASSERT(!image.isNull());
        return image;
    }

    return QImage();
}

QDate Model::date() const
{
    return m_date;
}

void Model::setDate(const QDate& value)
{
    if (value == m_date) {
        return;
    }
    m_date = value;
    emit dateChanged(m_date);
    search();
}

int Model::yearsAgo() const
{
    return m_yearsAgo;
}

void Model::setYearsAgo(int value)
{
    if( m_yearsAgo == value) {
        return;
    }
    m_yearsAgo = value;
    search();
}

void Model::search()
{
    // TODO [ab]: start as a separate thread
    //SearchThread* searchThread = new SearchThread();
    //connect(searchThread, &SearchThread::resultReady, this, &Model::handleResults);
    //connect(searchThread, &SearchThread::finished, searchThread, &QObject::deleteLater);
    //searchThread->start();

    if (m_date.isNull()) {
        return;
    }
    if (m_imageFolder.isEmpty()) {
        return;
    }

    m_imageYearsAgo = QImage(":/DummyImage.png");
    m_sameDateMatches.clear();
    emit imageYearsAgoChanged(m_imageYearsAgo);

    SearchAlgorithm algorithm(m_imageFolder, m_date.addYears(-m_yearsAgo));
    m_sameDateMatches = algorithm.search();

    if(m_sameDateMatches.isEmpty()) {
        // TODO: emit no result image
        emit matchCountChanged(0);
        return;
    }

    // need image reader to handle jpg orientation, QImage doesn't do it
    QImageReader reader(m_sameDateMatches[0]);
    reader.setAutoTransform(true);
    m_imageYearsAgo = reader.read();
    Q_ASSERT(!m_imageYearsAgo.isNull());
    emit imageYearsAgoChanged(m_imageYearsAgo);

    emit matchCountChanged(m_sameDateMatches.size());
}


