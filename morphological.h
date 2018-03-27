#ifndef MORPHOLOGICAL_H
#define MORPHOLOGICAL_H
#include "QImage"

enum operatorMorpho{
    EROSION,
    DILATE,
    OPENING,
    CLOSING
};

class morphological
{
public:
    morphological();
    void thresholding(int threshold, QImage image);
    void morpho(QImage,operatorMorpho);
    void saveImage(QImage);
    QImage getThresholdedImage(){return qThresholdedImage; }
    QImage getMorpologicalImage(){return qMorphologicalImage; }

    uchar* originalPixels;
    QImage savedImage;
    QImage qThresholdedImage;
    QImage qMorphologicalImage;
};

#endif // MORPHOLOGICAL_H
