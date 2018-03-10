#include "histogram.h"

histogram::histogram()
{

}

void histogram::calculateHistogram(QImage image){
    int imageSize = image.width() * image.height();
    uchar* originalPixels = image.bits();

    for (int pixel = 0; pixel < imageSize; pixel++) {
        int value =(int)originalPixels[pixel];
        histogramArray[value]++;
    }
}

void histogram::calculateAccumulatedFrequency(){
    accumulatedFrequency[0] = histogramArray[0];

    for (int frequency = 1; frequency < 256; frequency++) {
        accumulatedFrequency[frequency] = histogramArray[frequency];
    }
}

void histogram::equalizeHistogram(QImage image){
    qEqualizedImage = QImage(image.width(),image.width(), image.format());
    uchar* equalizedPixels = qEqualizedImage.bits();
    uchar* originalPixels = image.bits();

    calculateHistogram(image);
    calculateAccumulatedFrequency();

    float scale = 255.0f/accumulatedFrequency[255];
    for (int value = 0; value < 256; ++value) {
        newValues[value] = (scale * accumulatedFrequency[value]);
    }

    int imageSize = image.width() * image.height();

    for (int pixel = 0; pixel < imageSize; pixel++) {
        int value = (int)newValues[originalPixels[pixel]];
        equalizedPixels[pixel]=value;
        equalizedHistogram[value]++;
    }
}

int histogram::calculateThreshold(ThresMethod thres, QImage image){
    int threshold = 0;

    if(thres == ISODATA){
        calculateHistogram(image);
        calculateAccumulatedFrequency();
        int oldT = 0; newT = 128;

        while(oldT != newT){
            oldT = newT;
            float meanF = 0.0f;
            float meanB = 0.0f;

            for (int f = 0; f < newT; f++) {
                meanF += f * histogramArray[f];
            }

            meanF = meanF/accumulatedFrequency[newT-1];

            for (int b = newT; b < 256; b++) {
                meanB += b * histogramArray[b];
            }

            meanB = meanB / (accumulatedFrequency[255] - accumulatedFrequency[newT-1]);

            newT = (meanF + meanB) / 2;
        }
        return newT;
    }
}
