#include "ImageGenerator.h"

#include <QPainter>
#include <QPen>
#include <QFont>
#include <QString>
#include <QRectF>

QImage ImageGenerator::makeImage(const QImage& sourceImage)
{
    QString text =
        QString("%1\n %2 years ago").arg(m_date.toString(), QString::number(m_yearsAgo));

    QPainter p;
    QImage destImage = sourceImage.copy();
    bool ret = p.begin(&destImage);

    p.setPen(QPen(Qt::black));
    QFont font("Times");
    font.setBold(true);
    font.setPixelSize(destImage.rect().width()*0.08);
    p.setFont(font);
    p.drawText(destImage.rect().adjusted(-5, -5, -5, -5), Qt::AlignRight | Qt::AlignBottom, text);

    p.end();

    return destImage;
}

void ImageGenerator::setDate(const QDate& value)
{
    m_date = value;
}

void ImageGenerator::setYearsAgo(int value)
{
    m_yearsAgo = value;
}
