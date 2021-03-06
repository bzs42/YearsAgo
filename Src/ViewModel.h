#ifndef VIEWMODEL_H
#define VIEWMODEL_H

#include <QObject>

#include "Model.h"

class ViewModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString imageFolder READ imageFolder WRITE setImageFolder NOTIFY imageFolderChanged)
    Q_PROPERTY(QImage imageYearsAgo READ imageYearsAgo NOTIFY imageYearsAgoChanged)
    Q_PROPERTY(int yearsAgo READ yearsAgo WRITE setYearsAgo NOTIFY yearsAgoChanged)

public:
    ViewModel();

    // commands
    bool canBrowse() const;

    // properties
    bool canImageFolder() const;
    QString imageFolder() const;
    QImage imageYearsAgo() const;
    QDate date() const;

    bool canYearsAgo() const;
    int yearsAgo() const;
    int minYearsAgo() const;
    int maxYearsAgo() const;

    bool canNextImage() const;

public slots:
    void doNextImage();
    void setImageFolder(const QString& value);
    void setYearsAgo(int value);

signals:
    void canBrowseChanged(bool value);
    void canImageFolderChanged(bool value);
    void imageFolderChanged(const QString& value);
    void canYearsAgoChanged(bool value);
    void yearsAgoChanged(int value);
    void imageYearsAgoChanged(const QImage& value);
    void matchCountChanged(int value);
    void dateChanged(const QDate& value);
    void canNextImageChanged(bool value);

private:
    Model m_model;
    int m_matchCount;
    int m_matchNumber;
};

#endif // VIEWMODEL_H
