#include "View.h"
#include "./ui_View.h"

#include <QFileDialog>

View::View(QWidget *parent)
    : QDialog(parent)
    , m_ui(new Ui::View)
{
    m_ui->setupUi(this);

    m_ui->pushButtonBrowse->setEnabled(m_viewmodel.canBrowse());
    connect(&m_viewmodel, &ViewModel::canBrowseChanged, m_ui->pushButtonBrowse, &QPushButton::setEnabled);

    m_ui->labelImagePlaceholder->setScaledContents(true);
    m_ui->labelImagePlaceholder->setPixmap(m_viewmodel.imageOneYearAgo());
    connect(&m_viewmodel, &ViewModel::imageOneYearAgoChanged, m_ui->labelImagePlaceholder, &QLabel::setPixmap);

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
    delete m_ui;
}

