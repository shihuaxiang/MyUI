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
    static QPixmap magicAvatarSvg(const QPixmap &source, const QString &maskSvgFilePath, const QSize &size);

    /**
     * @brief According to mask crop avatar, and then add border
     */
    static void magicAvatar(QPixmap& avatar, const QPixmap& mask, const QPixmap& border);

    /**
     * @brief add avatar border
     */
    static void borderAvatar(QPixmap& avatar, const QPixmap& border);

    /**
     * @brief destImg add to srcImg,algin center
     */
    static QPixmap maskImage(const QPixmap& srcImg, const QPixmap& destImg);

private:
    static int sgn(double d);
};

#endif // IMAGEOP_H
