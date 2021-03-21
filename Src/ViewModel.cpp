#include "ViewModel.h"

#include <QPixmap>
#include <QTimer>

ViewModel::ViewModel()
    : m_isBusy(false)
{
    connect(&m_model, &Model::imageYearsAgoChanged, this, &ViewModel::imageYearsAgoChanged);
    connect(&m_model, &Model::dateChanged, this, &ViewModel::dateChanged);

    connect(&m_model, &Model::matchCountChanged, this, &ViewModel::matchCountChanged);
    connect(
        &m_model, &Model::matchCountChanged, this,
        [this](int value) {
            m_matchCount = value;
            m_matchNumber = 0;
            emit canNextImageChanged(m_matchCount != 0);
        });

    connect(&m_model, &Model::searchStarted, this,
        [this]() {
            setBusy(true);
        });
    connect(&m_model, &Model::searchFinished, this,
        [this]() {
            setBusy(false);
        });

    //QTimer::singleShot(10, &m_model, SLOT(setDate(QDate::currentDate())));
    QTimer::singleShot(10, this,[this](){ m_model.setDate(QDate::currentDate());});
}

auto ViewModel::canBrowse() const -> bool
{
    return true;
}

auto ViewModel::canImageFolder() const -> bool
{
    return false;
}

auto ViewModel::imageFolder() const -> QString
{
    return m_model.imageFolder();
}

QImage ViewModel::imageYearsAgo() const
{
    return m_model.imageYearsAgo(m_matchNumber);
}

QDate ViewModel::date() const
{
    return m_model.date();
}

bool ViewModel::canYearsAgo() const
{
    if(m_isBusy) {
        return false;
    }
    return true;
}

int ViewModel::yearsAgo() const
{
    return m_model.yearsAgo();
}

int ViewModel::minYearsAgo() const
{
    return 1;
}

int ViewModel::maxYearsAgo() const
{
    return 80;
}

bool ViewModel::canNextImage() const
{
    if(m_isBusy) {
        return false;
    }
    if(m_matchCount > 0) {
        return true;
    }
    return false;
}

void ViewModel::doNextImage()
{
    if(!canNextImage()) {
        return;
    }
    m_matchNumber++;
    if(m_matchNumber >= m_matchCount) {
        m_matchNumber = 0;
    }
    emit imageYearsAgoChanged(m_model.imageYearsAgo(m_matchNumber));
}

void ViewModel::setImageFolder(const QString& value)
{
    if(value == m_model.imageFolder()) {
        return;
    }

    m_model.setImageFolder(value);
    emit imageFolderChanged(m_model.imageFolder());
}

void ViewModel::setYearsAgo(int value)
{
    if(!canYearsAgo()) {
        return;
    }
    if(m_model.yearsAgo() == value) {
        return;
    }
    m_model.setYearsAgo(value);
}

void ViewModel::setBusy(bool value)
{
    if(m_isBusy == value ) {
        return;
    }

    m_isBusy = value;

    emit canBrowseChanged(canBrowse());
    emit canImageFolderChanged(canImageFolder());
    emit canNextImageChanged(canNextImage());
    emit canYearsAgoChanged(canYearsAgo());
}
