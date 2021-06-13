#include "ImageGenerator.h"

#include <QPainter>
#include <QPen>
#include <QFont>
#include <QString>
#include <QRectF>
#include <QFontMetrics>
#include <QLocale>

QImage ImageGenerator::makeImage(const QImage& sourceImage)
{
    QLocale locale(QLocale::German, QLocale::Germany);
    QString format("ddd, d.M.yyyy");
    QString text =            
        QString("%1 %2 Ago\n%3").arg(
            QString::number(m_yearsAgo),
            m_yearsAgo == 1 ? "Year" : "Years", 
            locale.toString(m_date.addYears(-m_yearsAgo), format));

    QPainter painter;
    QImage destImage = sourceImage.copy();
    bool ret = painter.begin(&destImage);

    QFont font("Times");
    font.setBold(true);
    font.setPixelSize(destImage.rect().width() * 0.05);
    painter.setFont(font);
    
    const auto imageRect = QRect(destImage.rect());
    const auto fontMetrics = QFontMetrics(font);
    const auto textRect = fontMetrics.boundingRect(
        imageRect.adjusted(5, 5, -10, -5), Qt::AlignRight | Qt::AlignBottom, text);

    int penWidth = 4;
    painter.setPen(QPen(QBrush(QColor(66, 17, 82)), penWidth));

    auto fillRect = textRect.adjusted(-5, 0, 10, 5);
    painter.fillRect(fillRect, QBrush(QColor(66, 17, 82, 127)));
    painter.drawRect(fillRect.adjusted(0, 0, -penWidth + 1, -penWidth + 1));

    painter.setPen(QPen(Qt::white));
    
    painter.drawText(
        textRect,
        Qt::AlignRight | Qt::AlignBottom,
        text);
 
    painter.end();

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
