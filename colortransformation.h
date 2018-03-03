#ifndef COLORTRANSFORMATION_H
#define COLORTRANSFORMATION_H

#include "QImage"

class ColorTransformation
{
public:
    ColorTransformation();
    void RGBtoHSL(QImage);
    void RGBtoHSV(QImage);
    QImage getHSLImage() {return HSLImage;}
    QImage getHSVImage() {return HSVImage;}

private:
    QImage HSLImage;
    QImage HSVImage;
};


#endif // COLORTRANSFORMATION_H
