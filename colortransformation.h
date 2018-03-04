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
    QImage getRedImage() {return red;}
    QImage getGreenImage() {return green;}
    QImage getBlueImage() {return blue;}

private:
    //The RGB images will be used to show the individuals channels of HSL and HSV images.
    QImage red;
    QImage green;
    QImage blue;
    QImage HSLImage;
    QImage HSVImage;
};

#endif // COLORTRANSFORMATION_H
