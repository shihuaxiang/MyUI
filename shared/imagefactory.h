#ifndef IMAGEFACTORY_H
#define IMAGEFACTORY_H

#include <QString>

class ImageFactory
{
public:
    ImageFactory();

    static void createTransparentImage100(QString fileName);
    static void createTransparentImage255(QString fileName);
    static void createTransparentImage(int radio, int margin, int alphaDelta, QString fileName);
};

#endif // IMAGEFACTORY_H
