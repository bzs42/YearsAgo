#include "View.h"
#include "./ui_View.h"

#include <QFileDialog>
#include <QSettings>

View::View(QWidget *parent)
    : QDialog(parent)
    , m_ui(new Ui::View)
{
    setWindowFlag(Qt::WindowMinimizeButtonHint, true);
    setWindowFlag(Qt::WindowMaximizeButtonHint, true);


    m_ui->setupUi(this);

    QSettings settings;
    restoreGeometry(settings.value("geometry").toByteArray());

    // label date
    m_ui->labelDate->setText(m_viewmodel.date().toString());
    connect(
        &m_viewmodel, &ViewModel::dateChanged, this,
        [this](const QDate& value) {
            m_ui->labelDate->setText(value.toString());
        });

    // spinBox yearsAgo
    m_ui->spinBox->setMaximum(m_viewmodel.maxYearsAgo());
    m_ui->spinBox->setMinimum(m_viewmodel.minYearsAgo());
    m_ui->spinBox->setValue(m_viewmodel.yearsAgo());
    m_ui->spinBox->setEnabled(m_viewmodel.canYearsAgo());
    connect(&m_viewmodel, &ViewModel::canYearsAgoChanged, m_ui->spinBox, &QSpinBox::setEnabled);
    connect(
        m_ui->spinBox, QOverload<int>::of(&QSpinBox::valueChanged), &m_viewmodel, &ViewModel::setYearsAgo);

    // label matchCount
    m_ui->labelMatchCount->setText("0");
    connect(
        &m_viewmodel, &ViewModel::matchCountChanged, this,
        [this](int value) {
            m_ui->labelMatchCount->setText(QString::number(value));
        });

    // pushButton nextImage
    m_ui->pushButtonShowNext->setEnabled(m_viewmodel.canNextImage());
    connect(&m_viewmodel, &ViewModel::canNextImageChanged, m_ui->pushButtonShowNext, &QPushButton::setEnabled);
    connect(m_ui->pushButtonShowNext, &QPushButton::clicked, &m_viewmodel, &ViewModel::doNextImage);

    // image
    // TODO: initial scale
    //m_ui->labelImagePlaceholder->setScaledContents(true);
    //m_ui->labelImagePlaceholder->setPixmap(QPixmap::fromImage(m_viewmodel.imageOneYearAgo()));
    setImage(m_viewmodel.imageYearsAgo());
    connect(&m_viewmodel, &ViewModel::imageYearsAgoChanged, this, &View::setImage);

    // lineEdit imageFolder
    m_ui->lineEditImageFolder->setText(m_viewmodel.imageFolder());
    m_ui->lineEditImageFolder->setEnabled(m_viewmodel.canImageFolder());
    connect(&m_viewmodel, &ViewModel::imageFolderChanged, m_ui->lineEditImageFolder, &QLineEdit::setText);

    // pushButton browse
    m_ui->pushButtonBrowse->setEnabled(m_viewmodel.canBrowse());
    connect(&m_viewmodel, &ViewModel::canBrowseChanged, m_ui->pushButtonBrowse, &QPushButton::setEnabled);
    connect(
        m_ui->pushButtonBrowse, &QPushButton::clicked, this,
        [this]()
        {
            QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), m_viewmodel.imageFolder());
            if(!dir.isEmpty())
            {
                m_viewmodel.setImageFolder(dir);
            }
        });

    // window title
    setWindowTitle(QString::number(m_viewmodel.yearsAgo()) + QString(" Years ago"));
    connect(
        m_ui->spinBox, QOverload<int>::of(&QSpinBox::valueChanged), this,
        [this]() {
            setWindowTitle(QString::number(m_viewmodel.yearsAgo()) + QString(" Years ago"));
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
    setImage(m_viewmodel.imageYearsAgo());
}
