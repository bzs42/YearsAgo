#include "Model.h"

#include <QDebug>
#include <QDirIterator>
#include <QImage>
#include <QImageReader>
#include <QRegularExpression>
#include <QSettings>

#include "SearchThread.h"


Model::Model()
    : m_yearsAgo(1)
    , m_isSearching(false)
{
    QSettings settings;
    m_imageFolder = settings.value("imageFolder", QString()).toString();

    qRegisterMetaType<QMap<QString, QVector<QString>>>("QMap<QString, QVector<QString>");
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

    QString year = QString::number(m_date.addYears(-yearsAgo()).year());

    if(!m_sameDateMatches.contains(year)) {
        return QImage();
    }

    if(matchNumber > 0 && matchNumber < m_sameDateMatches.value(year).size())
    {
        QImageReader reader(m_sameDateMatches.value(year)[matchNumber]);
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

void Model::onSearchResultReady(QMap<QString, QVector<QString>> value)
{
    m_isSearching = false;
    emit searchFinished();

    m_imageYearsAgo = QImage(":/SearchingFinished.png");

    m_sameDateMatches = value;

    QString year = QString::number(m_date.addYears(-yearsAgo()).year());
    if(!m_sameDateMatches.contains(year)) {
        emit imageYearsAgoChanged(m_imageYearsAgo);
        emit matchCountChanged(0);
        return;
    }

    // need image reader to handle jpg orientation, QImage doesn't do it
    QImageReader reader(m_sameDateMatches.value(year)[0]);
    reader.setAutoTransform(true);
    m_imageYearsAgo = reader.read();
    Q_ASSERT(!m_imageYearsAgo.isNull());
    emit imageYearsAgoChanged(m_imageYearsAgo);

    emit matchCountChanged(m_sameDateMatches.value(year).size());
}

void Model::search()
{
    if (m_date.isNull()) {
        return;
    }
    if (m_imageFolder.isEmpty()) {
        return;
    }
    if(m_isSearching) {
        return;
    }

    m_isSearching = true;
    emit searchStarted();

    m_imageYearsAgo = QImage(":/SearchingStarted.png");
    emit imageYearsAgoChanged(m_imageYearsAgo);

    auto* searchThread = new SearchThread(m_imageFolder, m_date.addYears(-m_yearsAgo), this);
    connect(searchThread, &SearchThread::searchResultReady, this, &Model::onSearchResultReady);
    connect(searchThread, &SearchThread::finished, searchThread, &QObject::deleteLater);
    searchThread->start();
}


