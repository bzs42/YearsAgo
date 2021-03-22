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
    bool canNextImage() const;
    bool canShare() const;

    // properties
    bool canImageFolder() const;
    QString imageFolder() const;
    QImage imageYearsAgo() const;
    QDate date() const;

    bool canYearsAgo() const;
    int yearsAgo() const;
    int minYearsAgo() const;
    int maxYearsAgo() const;

public slots:
    void doNextImage();
    void doShare();
    void setImageFolder(const QString& value);
    void setYearsAgo(int value);
    void setBusy(bool value);

signals:
    void canBrowseChanged(bool value);
    void canNextImageChanged(bool value);
    void canShareChanged(bool value);
    void canImageFolderChanged(bool value);
    void imageFolderChanged(const QString& value);
    void canYearsAgoChanged(bool value);
    void yearsAgoChanged(int value);
    void imageYearsAgoChanged(const QImage& value);
    void matchCountChanged(int value);
    void dateChanged(const QDate& value);

private:
    Model m_model;
    int m_matchCount;
    int m_matchNumber;
    bool m_isBusy;
};

#endif // VIEWMODEL_H
