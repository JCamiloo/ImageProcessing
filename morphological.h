#ifndef MORPHOLOGICAL_H
#define MORPHOLOGICAL_H
#include "QImage"

enum operatorMorpho{
    EROSION,
    DILATE,
    OPENING,
    CLOSING,
    GSEROSION,
    GSDILATE,
    GSOPENING,
    GSCLOSING,
    GRADIENT,
    TOPHAT,
    OTHER
};

class morphological
{
public:
    morphological();
    void thresholding(int threshold, QImage image);
    void morpho(QImage,operatorMorpho);
    void saveImage(QImage);
    void setOriginalImage(QImage);
    QImage getThresholdedImage(){return qThresholdedImage; }
    QImage getMorpologicalImage(){return qMorphologicalImage; }

    uchar* originalPixels;
    QImage savedImage;
    QImage qThresholdedImage;
    QImage qMorphologicalImage;
};

#endif // MORPHOLOGICAL_H
