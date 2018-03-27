#include "morphological.h"

morphological::morphological()
{

}

void morphological::thresholding(int threshold, QImage image){
    originalPixels = image.bits();
    qThresholdedImage = QImage(image.width(), image.height(), QImage::Format_Grayscale8);
    qMorphologicalImage = QImage(image.width(), image.height(), QImage::Format_Grayscale8);
    uchar* thresholdedPixels = qThresholdedImage.bits();

    int imageSize = image.width() * image.height();

    for (int pixel = 0; pixel < imageSize; pixel++) {
        thresholdedPixels[pixel]=originalPixels[pixel]<threshold ? 0:255;
    }
}

void morphological::morpho(QImage image, operatorMorpho opMorpho){
    qMorphologicalImage = QImage(image.width(), image.height(), QImage::Format_Grayscale8);
    uchar* morphologicalPixels = qMorphologicalImage.bits();
    int kernel_width = 7;
    int kernel_height = 7;
    int stride_x = 3;
    int stride_y = 3;

    int kernel[49] = {0, 0, 1, 1, 1, 0, 0,
                      0, 1, 1, 1, 1, 1, 0,
                      1, 1, 1, 1, 1, 1, 1,
                      1, 1, 1, 1, 1, 1, 1,
                      1, 1, 1, 1, 1, 1, 1,
                      0, 1, 1, 1, 1, 1, 0,
                      0, 0, 1, 1, 1, 0, 0};

    int sizeBlock = kernel_width * kernel_height;
    uchar* block = (uchar*)malloc(sizeBlock * sizeof(uchar));

    if(opMorpho == EROSION){
        for (int y = 3; y < image.height()-3; y++) {
            for (int x = 3; x < image.width()-3; x++) {

                for (int kernel_y = 0; kernel_y < kernel_height; kernel_y++) {
                    for (int kernel_x = 0; kernel_x < kernel_width; kernel_x++) {
                        block[kernel_x + (kernel_y * kernel_width)] = savedImage.pixelColor((x - stride_x) + kernel_x, (y  - stride_y) + kernel_y).value();
                    }

                    bool containsAll = true;
                    for (int i = 0; i < sizeBlock; i++) {
                        if(kernel[i] == 1 && (int)block[i]==0){
                            containsAll = false;
                            break;
                        }
                    }
                    morphologicalPixels[x + (y * image.width())] = (containsAll == true) ? 255: 0;
                }
                free(block);
            }
        }
    }

    if(opMorpho == DILATE){
        for (int y = 3; y < image.height()-3; y++) {
            for (int x = 3; x < image.width()-3; x++) {

                for (int kernel_y = 0; kernel_y < kernel_height; kernel_y++) {
                    for (int kernel_x = 0; kernel_x < kernel_width; kernel_x++) {
                        block[kernel_x + (kernel_y * kernel_width)] = savedImage.pixelColor((x - stride_x) + kernel_x, (y  - stride_y) + kernel_y).value();
                    }

                    bool containsAll = false;
                    for (int i = 0; i < sizeBlock; i++) {
                        if(kernel[i] == 1 && (int)block[i]==255){
                            containsAll = true;
                            break;
                        }
                    }
                    morphologicalPixels[x + (y * image.width())] = (containsAll == true) ? 255: 0;
                }
                free(block);
            }
        }
    }
}

void morphological::saveImage(QImage img){
    this->savedImage = img;
}
