#include "imagefactory.h"
#include <QImage>

ImageFactory::ImageFactory()
{

}

void ImageFactory::createTransparentImage100(QString fileName)
{
    int radio = 100;

    QImage image(radio*2+1, radio*2+1, QImage::Format_ARGB32);

    int i, j, k;
    int alpha = 0;
    double alphaDelta = 255.0 / radio;
    QRgb value;

    for(i = -radio; i <= radio ; i++)
    {
        for(j = -radio; j <= radio ; j++)
        {
            k = std::max(std::abs(i), std::abs(j));
            alpha = int((radio - k) * alphaDelta);
            value = qRgba(0, 0, 0, alpha);

            image.setPixel(j+radio, i+radio, value);
        }
    }

    image.save(fileName);
}

void ImageFactory::createTransparentImage255(QString fileName)
{
    int radio = 255;

    QImage image(radio*2+1, radio*2+1, QImage::Format_ARGB32);


    int i, j, k;
    int alpha = 0;
    QRgb value;

    for(i = -radio; i <= radio ; i++)
    {
        for(j = -radio; j <= radio ; j++)
        {
            k = std::max(std::abs(i), std::abs(j));
            alpha = radio - k;
            value = qRgba(0, 0, 0, alpha);

            image.setPixel(j+radio, i+radio, value);
        }
    }

    image.save(fileName);
}

void ImageFactory::createTransparentImage(int radio, int margin, int alphaDelta, QString fileName)
{
    QImage image(radio*2+1, radio*2+1, QImage::Format_ARGB32);

    int i, j, k;
    int alpha = 0;
    QRgb value;

    for(i = -radio; i <= radio ; i++)
    {
        for(j = -radio; j <= radio ; j++)
        {
            k = radio - std::max(std::abs(i), std::abs(j));
            if (k < margin)
                alpha = k * alphaDelta;
            else
                alpha = 0;

            value = qRgba(0, 0, 0, alpha);

            image.setPixel(j+radio, i+radio, value);
        }
    }

    image.save(fileName);
}

