#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include <QImage>
#include <string>
#include <iostream>

enum ThresMethod{
    ISODATA,
    OTSU
};

class histogram
{
public:
    histogram();
    void calculateHistogram(QImage image);
    void calculateAccumulatedFrequency();
    void equalizeHistogram(QImage image);    
    int calculateThreshold(ThresMethod thres, QImage);
    void thresholding(int,QImage);

    int* getHistogram()              {return histogramArray; }
    int* getEqualizedHistogram()     {return equalizedHistogram; }
    int* getAccumulatedFrequency()   {return accumulatedFrequency; }

    uchar* originalPixels;

    QImage getEqualizedImage(){return qEqualizedImage;}
    QImage getThresholdedImage(){return qThresholdedImage;}

private:

    int histogramArray[256] = {};
    int accumulatedFrequency[256] = {};
    int equalizedHistogram[256] = {};
    int newValues[256] = {};

    QImage  qOriginalImage;
    QImage  qEqualizedImage;
    QImage  qThresholdedImage;
};

#endif // HISTOGRAM_H
