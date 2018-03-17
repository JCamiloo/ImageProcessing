#include "histogram.h"
#include "QImageWriter"
histogram::histogram()
{

}

void histogram::calculateHistogram(QImage image){
    originalPixels = image.bits();
    int imageSize = image.width() * image.height();

    for (int pixel = 0; pixel < imageSize; pixel++) {
        int value =(int)originalPixels[pixel];
        histogramArray[value]++;
    }
}

void histogram::calculateAccumulatedFrequency(){
    accumulatedFrequency[0] = histogramArray[0];

    for (int frequency = 1; frequency < 256; frequency++) {
        accumulatedFrequency[frequency] = histogramArray[frequency] +  accumulatedFrequency[frequency-1];
    }
}

void histogram::equalizeHistogram(QImage image){

    qEqualizedImage = QImage(image.width(),image.height(),QImage::Format_Grayscale8);
    uchar* equalizedPixels = qEqualizedImage.bits();

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
        int oldT = 0, newT = 128;

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

    else if(thres==OTSU){
        calculateHistogram(image);
        calculateAccumulatedFrequency();

        int imageSize = image.width() * image.height();
        int     sum = 0;
        int     q1 = 0; // class 1
        int     q2 = 0; // class 2
        float   meanF = 0.0;
        float   max = 0;  // maximun -- threshold

        for (int i = 0; i < 256; i++){
          sum += i * ((int)histogramArray[i]);
        }

        for (int i = 0 ; i <256 ; i++) {

            q1 += histogramArray[i];
            q2 = imageSize - q1;

            meanF += (float) (i * ((int)histogramArray[i]));
            float m1 = meanF / q1;
            float m2 = (sum - meanF) / q2;

            float temp = (float) q1 * (float) q2 * (m1 - m2) * (m1 - m2);

            // Update the threshold if necessary
            if (temp > max) {
              max = temp;
              threshold = i;
            }
        }
        return threshold;
    }
}

void histogram::thresholding(int threshold,QImage image){
    qThresholdedImage = QImage(image.width(), image.height(), image.format());
    uchar* originalPixels = image.bits();
    uchar* thresholdedPixels = qThresholdedImage.bits();

    int imageSize = image.width() * image.height();

    for (int pixel = 0; pixel < imageSize; pixel++) {
        thresholdedPixels[pixel]=originalPixels[pixel]<threshold ? 0:255;
    }
}
