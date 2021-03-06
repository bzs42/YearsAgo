#include "View.h"
#include "./ui_View.h"

#include <QFileDialog>
#include <QSettings>

View::View(QWidget *parent)
    : QDialog(parent)
    , m_ui(new Ui::View)
{
    m_ui->setupUi(this);

    QSettings settings;
    restoreGeometry(settings.value("geometry").toByteArray());

    m_ui->pushButtonBrowse->setEnabled(m_viewmodel.canBrowse());
    connect(&m_viewmodel, &ViewModel::canBrowseChanged, m_ui->pushButtonBrowse, &QPushButton::setEnabled);

    // TODO: initial scale
    //m_ui->labelImagePlaceholder->setScaledContents(true);
    //m_ui->labelImagePlaceholder->setPixmap(QPixmap::fromImage(m_viewmodel.imageOneYearAgo()));
    setImage(m_viewmodel.imageOneYearAgo());
    connect(&m_viewmodel, &ViewModel::imageOneYearAgoChanged, this, &View::setImage);

    m_ui->lineEditImageFolder->setText(m_viewmodel.imageFolder());
    m_ui->lineEditImageFolder->setEnabled(m_viewmodel.canImageFolder());
    connect(&m_viewmodel, &ViewModel::imageFolderChanged, m_ui->lineEditImageFolder, &QLineEdit::setText);

    connect(
        m_ui->pushButtonBrowse, &QPushButton::clicked, this,
        [this]()
        {
            QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"));
            if(!dir.isEmpty())
            {
                m_viewmodel.setImageFolder(dir);
            }
        });
}

View::~View()
{
    QSettings settings;
    settings.setValue("geometry", saveGeometry());
    delete m_ui;
}

void View::setImage(const QImage& value)
{
    QSize size = m_ui->labelImagePlaceholder->size();
    m_ui->labelImagePlaceholder->setPixmap(
        QPixmap::fromImage(value).scaled(
            size.width(), size.height(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}


void View::resizeEvent(QResizeEvent* event)
{
    QDialog::resizeEvent(event);
    setImage(m_viewmodel.imageOneYearAgo());
}
