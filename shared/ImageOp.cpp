#include "ImageOp.h"
#include <QSvgRenderer>

ImageOp::ImageOp()
{

}

std::vector<QPointF> ImageOp::superEllipse(double a, double b, double m, double n, double precision, int xCenter, int yCenter)
{
    if (precision >= 1.00 || precision < 0.001)
    {
        qDebug() << "use numbers from range [0.001 ; 1.00) for precision parametr";
    }

    std::vector<QPointF> points;
    QPointF temp;
    QPointF P;
    for (double d = -1.0; d < 1.00; d += precision) {
        double t = d*M_PI;
        double x = pow(std::abs(cos(t)),2.0/m) * a * sgn(cos(t));
        double y = pow(std::abs(sin(t)),2.0/n) * b * sgn(sin(t));
        P = QPointF(x + xCenter, y + yCenter);
        if (P != temp) // ignore dublicates
            points.push_back(P);
        temp = P;
    }
    return points;
}

void ImageOp::magicAvatar(QPixmap &avatar, const QPixmap &mask)
{
    QSize sz = mask.size();

    avatar = avatar.scaled(sz);

    QSize subMask = sz - mask.size();

    QImage resultImage = QImage(sz, QImage::Format_ARGB32_Premultiplied);
    QPainter painter(&resultImage);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.fillRect(resultImage.rect(), Qt::transparent);
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter.drawPixmap(subMask.width()/2, subMask.height()/2, mask);
    painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
    painter.drawPixmap(0, 0, avatar);
    painter.setCompositionMode(QPainter::CompositionMode_DestinationOver);
    painter.fillRect(resultImage.rect(), Qt::transparent);
    painter.end();

    avatar = avatar.fromImage(resultImage);
}

QPixmap ImageOp::magicAvatarSvg(const QPixmap &source, const QString &maskSvgFilePath, const QSize &size)
{
    QImage mask(size, QImage::Format_ARGB32_Premultiplied);
    mask.fill(Qt::transparent);
    QPainter maskPainter(&mask);
    maskPainter.setRenderHint(QPainter::Antialiasing);
    QSvgRenderer svgRender(maskSvgFilePath);
    svgRender.render(&maskPainter);
    maskPainter.end();

    QPixmap sourceCopy = source;
    magicAvatar(sourceCopy, QPixmap::fromImage(mask));
    return sourceCopy;
}

void ImageOp::magicAvatar(QPixmap &avatar, const QPixmap &mask, const QPixmap &border)
{
    QSize sz = border.size();
    avatar = avatar.scaled(sz);
    QSize subMask = sz - mask.size();

    QImage resultImage = QImage(sz, QImage::Format_ARGB32_Premultiplied);
    QPainter painter(&resultImage);
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.fillRect(resultImage.rect(), Qt::transparent);
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter.drawPixmap(subMask.width()/2, subMask.height()/2, mask);
    painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
    painter.drawPixmap(0, 0, avatar);
    painter.setCompositionMode(QPainter::CompositionMode_DestinationOver);
    painter.fillRect(resultImage.rect(), Qt::transparent);
    painter.drawPixmap(0, 0, border);
    painter.end();

    avatar = avatar.fromImage(resultImage);
}

void ImageOp::borderAvatar(QPixmap &avatar, const QPixmap &border)
{
    QSize sz = border.size();
    QSize subSz = sz - avatar.size();

    QImage resultImage = QImage(sz, QImage::Format_ARGB32_Premultiplied);
    QPainter painter(&resultImage);
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.fillRect(resultImage.rect(), Qt::transparent);
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter.drawPixmap(subSz.width()/2, subSz.height()/2, avatar);
    painter.setCompositionMode(QPainter::CompositionMode_DestinationOver);
    painter.fillRect(resultImage.rect(), Qt::transparent);
    painter.drawPixmap(0, 0, border);
    painter.end();

    avatar = avatar.fromImage(resultImage);
}

QPixmap ImageOp::maskImage(const QPixmap &srcImg, const QPixmap &destImg)
{
    QSize sub = srcImg.size() - destImg.size();

    QPixmap resultImg = srcImg;
    QPainter painter(&resultImg);

    // add middle mask
    QImage mask = QImage(srcImg.size(), QImage::Format_ARGB32_Premultiplied);
    QImage lower = QImage(srcImg.size(), QImage::Format_ARGB32_Premultiplied);
    lower.fill("#000000");
    QPainter painterMask(&mask);
    painterMask.setCompositionMode(QPainter::CompositionMode_Source);
    painterMask.fillRect(mask.rect(), Qt::transparent);
    painterMask.setCompositionMode(QPainter::CompositionMode_SourceOver);
    painterMask.drawPixmap(0, 0, srcImg);
    painterMask.setCompositionMode(QPainter::CompositionMode_SourceIn);
    painterMask.drawImage(0, 0, lower);
    painterMask.setCompositionMode(QPainter::CompositionMode_DestinationOver);
    painterMask.fillRect(mask.rect(), Qt::transparent);
    painterMask.end();

    // add dest image
    painter.setOpacity(0.3);
    painter.drawImage(0, 0, mask);
    if (!destImg.isNull())
    {
        painter.setOpacity(1);
        painter.drawPixmap(sub.width()/2, sub.height()/2, destImg);
    }
    painter.end();
    return resultImg;
}

int ImageOp::sgn(double d)
{
    if (d < 0)
        return -1;
    if (d == 0)
        return 0;
    if (d > 0)
        return 1;
}

