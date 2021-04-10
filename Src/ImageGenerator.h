#ifndef IMAGEGENERATOR_H
#define IMAGEGENERATOR_H

#include <QDate>
#include <QImage>

class ImageGenerator
{
public:
    ImageGenerator() = default;
    QImage makeImage(const QImage& sourceImage);
    void setDate(const QDate& value);
    void setYearsAgo(int value);

private:
    QDate m_date;
    int m_yearsAgo;
};

#endif // IMAGEGENERATOR_H
