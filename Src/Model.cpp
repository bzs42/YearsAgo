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
    m_imageYearsAgo = QImage(":/NoImageFound.png");
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
    int year = m_date.addYears(-m_yearsAgo).year();
    int count = getImageCount(m_date.addYears(-m_yearsAgo).year());

    if(matchNumber >= 0 && matchNumber < count) {
        return getImage(year, matchNumber);
    }

    return QImage(":/NoImageFound.png");
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

    int year = m_date.addYears(-m_yearsAgo).year();
    int count = getImageCount(m_date.addYears(-m_yearsAgo).year());

    if(count == 0) {
        m_imageYearsAgo = QImage(":/NoImageFound.png");
    }
    else {
        m_imageYearsAgo = getImage(year, 0);
    }

    emit imageYearsAgoChanged(m_imageYearsAgo);
    emit matchCountChanged(count);
}

void Model::onSearchResultReady(QMap<QString, QVector<QString>> value)
{
    m_isSearching = false;
    m_sameDateMatches = value;

    int year = m_date.addYears(-m_yearsAgo).year();
    int count = getImageCount(m_date.addYears(-m_yearsAgo).year());

    if(count == 0) {
        m_imageYearsAgo = QImage(":/SearchingFinished.png");
    }
    else {
        m_imageYearsAgo = getImage(year, 0);
    }

    emit searchFinished();
    emit imageYearsAgoChanged(m_imageYearsAgo);
    emit matchCountChanged(count);
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

    auto* searchThread = new SearchThread(m_imageFolder, m_date, this);
    connect(searchThread, &SearchThread::searchResultReady, this, &Model::onSearchResultReady);
    connect(searchThread, &SearchThread::finished, searchThread, &QObject::deleteLater);
    searchThread->start();
}

int Model::getImageCount(int year) const
{
    if(!m_sameDateMatches.contains(QString::number(year))) {
        return 0;
    }
    return m_sameDateMatches.value(QString::number(year)).size();
}

QImage Model::getImage(int year, int index) const
{
    if(getImageCount(year) == 0) {
        return QImage(":/NoImageFound.png");
    }

    // need image reader to handle jpg orientation, QImage doesn't do it
    QImageReader reader(m_sameDateMatches.value(QString::number(year))[index]);
    reader.setAutoTransform(true);
    QImage image = reader.read();
    Q_ASSERT(!image.isNull());
    return image;
}


