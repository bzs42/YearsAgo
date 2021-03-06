#ifndef VIEWMODEL_H
#define VIEWMODEL_H

#include <QObject>

#include "Model.h"

class ViewModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString imageFolder READ imageFolder WRITE setImageFolder NOTIFY imageFolderChanged)
    Q_PROPERTY(QPixmap imageOneYearAgo READ imageOneYearAgo NOTIFY imageOneYearAgoChanged)

public:
    ViewModel();

    // commands
    bool canBrowse() const;

    // properties
    bool canImageFolder() const;
    QString imageFolder() const;
    QPixmap imageOneYearAgo() const;

public slots:
    void browse();
    void setImageFolder(const QString& value);

signals:
    void canBrowseChanged(bool value);
    void canImageFolderChanged(bool value);
    void imageFolderChanged(const QString& value);
    void imageOneYearAgoChanged(const QPixmap& value);

private:
    Model m_model;
};

#endif // VIEWMODEL_H
