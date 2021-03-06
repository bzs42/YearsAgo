#include "ViewModel.h"

#include <QPixmap>
#include <QTimer>

ViewModel::ViewModel()
{
    connect(
        &m_model, &Model::imageOneYearAgoChanged,
        [this]() {
            emit imageOneYearAgoChanged(imageOneYearAgo());
        });
    QTimer::singleShot(10, &m_model, SLOT(setDate(QDate())));
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

QPixmap ViewModel::imageOneYearAgo() const
{
    return QPixmap::fromImage(m_model.imageOneYearAgo());
}

void ViewModel::browse()
{
    // TODO
}

void ViewModel::setImageFolder(const QString& value)
{
    if(value == m_model.imageFolder()) {
        return;
    }

    m_model.setImageFolder(value);
    emit imageFolderChanged(m_model.imageFolder());
}
