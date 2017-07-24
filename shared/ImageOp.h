#ifndef IMAGEOP_H
#define IMAGEOP_H
#include <QPainter>
#include <QtMath>
#include <QDebug>
#include <vector>

class ImageOp
{
public:
    ImageOp();

    /**
     * @brief get superEllipse points to draw
     */
    static std::vector<QPointF> superEllipse(double a, double b, double m, double n, double precision = 0.01, int xCenter = 200, int yCenter = 200);

    /**
     * @brief According to mask crop avatar
     */
    static void magicAvatar(QPixmap& avatar, const QPixmap& mask);

    /**
     * @brief crop source to specific size, use svg format to antialiasing
     */
    static QPixmap magicAvatarSvg(const QPixmap &source, const QSize &size);
    static QPixmap magicAvatarSvg(const QPixmap &source, const QPixmap &border);
    static QPixmap magicAvatarSvg(const QPixmap &source, const QString &svgBorder, const QSize& svgSize);

    /**
     * @brief According to mask crop avatar, and then add border
     */
    static void magicAvatar(QPixmap& avatar, const QPixmap& mask, const QPixmap& border);

    /**
     * @brief add avatar border
     */
    static void borderAvatar(QPixmap& avatar, const QPixmap& border);

    /**
     * @brief dest svg img add to default img,algin center (no border)
     */
    static QPixmap maskDefaultImage(const QSize& size, const QString& destSvgImg, const QSize& destSvgSize,
                                    double opacity = 0.5, const QColor& color = QColor("F8F8F8"));

    /**
     * @brief dest svg img add to default img,algin center (have border)
     */
    static QPixmap maskDefaultImage(const QString& borderSvgImg, const QSize& borderSvgSize,
                                    const QString& destSvgImg, const QSize& destSvgSize,
                                    double opacity = 0.5, const QColor& color = QColor("F8F8F8"));

    /**
     * @brief mask srcImg
     */
    static QPixmap maskImage(const QPixmap& srcImg, double opacity = 0.5);

    /**
     * @brief destImg add to srcImg,algin center
     */
    static QPixmap maskImage(const QPixmap& srcImg, const QPixmap& destImg, double opacity = 0.5);

    /**
     * @brief dest Svg Img add to srcImg,algin center
     */
    static QPixmap maskSvgImage(const QPixmap& srcImg, const QString& destSvgImg, const QSize& size, double opacity = 0.5);

    /**
     * @brief adjust source to specific size, use svg format to antialiasing
     */
    static QPixmap makeSvgPixmap(const QString fileName, const QSize &size);

    static QByteArray pixmapToByteArray(const QPixmap &pixmap, int quality);
    static void exsampleOutput(QString text, QString pixmapFileName, QString savedFileName);
    static void exsampleInput(QString loadFileName);

private:
    static int sgn(double d);

	static QSize scaleSizeByDeviceRatio(const QSize &size);
};

#endif // IMAGEOP_H
