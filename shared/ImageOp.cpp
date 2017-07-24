#include <QSvgRenderer>
#include <QApplication>
#include <QDesktopWidget>
#include <QBuffer>
#include <QFile>

#include "ImageOp.h"

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

QPixmap ImageOp::magicAvatarSvg(const QPixmap &source, const QSize &size)
{
    QImage mask(scaleSizeByDeviceRatio(size), QImage::Format_ARGB32_Premultiplied);
    mask.fill(Qt::transparent);
    QPainter maskPainter(&mask);
    maskPainter.setRenderHint(QPainter::Antialiasing);
    QSvgRenderer svgRender(QString(":/utils/images/avatar_dest.svg"));
    svgRender.render(&maskPainter);
    maskPainter.end();

    QPixmap sourceCopy = source;
    magicAvatar(sourceCopy, QPixmap::fromImage(mask));
    return sourceCopy;
}

QPixmap ImageOp::magicAvatarSvg(const QPixmap &avatar, const QPixmap &border) // use border's size
{
    QPixmap result = magicAvatarSvg(avatar, border.size());
    // maybe size changed in magicAvatarSvg function
    QPixmap borderCopy = border.scaled(result.width(), result.height(), Qt::KeepAspectRatio);
    QPainter painter(&result);
    painter.drawPixmap(0, 0, borderCopy);
    painter.end();
    return result;
}

QPixmap ImageOp::magicAvatarSvg(const QPixmap &source, const QString &svgBorder, const QSize &svgSize)
{
    QPixmap avatar = magicAvatarSvg(source, svgSize);
    QImage mask(scaleSizeByDeviceRatio(svgSize), QImage::Format_ARGB32_Premultiplied);
    mask.fill(Qt::transparent);
    QRect rc(0, 0, mask.width(), mask.height());
    QPainter painter(&mask);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawPixmap(rc.adjusted(1, 1, -1, -1), avatar);
    QSvgRenderer svgRender(svgBorder);
    svgRender.render(&painter);
    painter.end();
    return QPixmap::fromImage(mask);
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

QPixmap ImageOp::maskDefaultImage(const QSize &size, const QString &destSvgImg, const QSize &destSvgSize, double opacity, const QColor& color)
{
    QImage mask(scaleSizeByDeviceRatio(size), QImage::Format_ARGB32_Premultiplied);
    mask.fill(color);
    QPixmap avatar = magicAvatarSvg(QPixmap::fromImage(mask), size);
    return maskSvgImage(avatar, destSvgImg, destSvgSize, opacity);
}

QPixmap ImageOp::maskDefaultImage(const QString &borderSvgImg, const QSize &borderSvgSize,
                                  const QString &destSvgImg, const QSize &destSvgSize,
                                  double opacity, const QColor& color)
{
    QImage mask(scaleSizeByDeviceRatio(borderSvgSize), QImage::Format_ARGB32_Premultiplied);
    mask.fill(color);
    QPixmap avatar = magicAvatarSvg(QPixmap::fromImage(mask), borderSvgImg, borderSvgSize);
    return maskSvgImage(avatar, destSvgImg, destSvgSize, opacity);
}

QPixmap ImageOp::maskImage(const QPixmap &srcImg, double opacity)
{
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
    painter.setOpacity(opacity);
    painter.drawImage(0, 0, mask);
    painter.end();
    return resultImg;
}

QPixmap ImageOp::maskImage(const QPixmap &srcImg, const QPixmap &destImg, double opacity)
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
    painter.setOpacity(opacity);
    painter.drawImage(0, 0, mask);
    if (!destImg.isNull())
    {
        painter.setOpacity(1);
        painter.drawPixmap(sub.width()/2, sub.height()/2, destImg);
    }
    painter.end();
    return resultImg;
}

QPixmap ImageOp::maskSvgImage(const QPixmap &srcImg, const QString &destSvgImg, const QSize &size, double opacity)
{
    QSize destSize = scaleSizeByDeviceRatio(size);
    QSize sub = srcImg.size() - destSize;

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
    painter.setOpacity(opacity);
    painter.drawImage(0, 0, mask);
    if (!destSvgImg.isEmpty())
    {
        painter.setOpacity(1);
        QRect rc(0, 0, mask.width(), mask.height());
        rc.adjust(sub.width()/2, sub.height()/2, -sub.width()/2, -sub.height()/2);
        QSvgRenderer svgRender(destSvgImg);
        svgRender.render(&painter, rc);
    }
    painter.end();
    return resultImg;
}

QPixmap ImageOp::makeSvgPixmap(const QString fileName, const QSize &size)
{
    QImage mask(scaleSizeByDeviceRatio(size), QImage::Format_ARGB32_Premultiplied);
    mask.fill(Qt::transparent);
    QPainter maskPainter(&mask);
    maskPainter.setRenderHint(QPainter::Antialiasing);

    QSvgRenderer svgRender(fileName);
    svgRender.render(&maskPainter);
    maskPainter.end();

    return QPixmap::fromImage(mask);
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

QSize ImageOp::scaleSizeByDeviceRatio(const QSize &size)
{
	int ratio = QApplication::desktop()->devicePixelRatio();
	return size.scaled(size.width() * ratio, size.height() * ratio, Qt::KeepAspectRatio);
}

QByteArray ImageOp::pixmapToByteArray(const QPixmap &pixmap, int quality)
{
    QByteArray bytes;
    QBuffer buffer(&bytes);
    buffer.open(QIODevice::WriteOnly);
    pixmap.save(&buffer, "PNG", quality);

    return bytes;
}

void ImageOp::exsampleOutput(QString text, QString pixmapFileName, QString savedFileName)
{
    QFile saveFile(savedFileName);
    if (!saveFile.open(QIODevice::WriteOnly)) {
        return;
    }

    QDataStream ds(&saveFile);

    QPixmap pixmap(pixmapFileName);
    bool b = pixmap.isNull();
    QByteArray ba = ImageOp::pixmapToByteArray(pixmap, -1);

    ds << text;
    ds.writeBytes(ba.data(), ba.size());

    saveFile.close();
}

void ImageOp::exsampleInput(QString loadFileName)
{
    QFile loadFile(loadFileName);
    if (!loadFile.open(QIODevice::ReadOnly)) {
        return;
    }

    QDataStream ds(&loadFile);

    QString text;
    QPixmap pixmap;

    ds >> text;

    char* pixmapDataPtr = NULL;
    uint pixmapDataLen = 0;
    ds.readBytes(pixmapDataPtr, pixmapDataLen);
    pixmap.loadFromData((uchar*)pixmapDataPtr, pixmapDataLen);

    if (!pixmap.isNull())
        pixmap.save("d://1.jpg");

    qDebug() << text;

    loadFile.close();
}
