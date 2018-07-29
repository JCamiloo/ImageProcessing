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
    originalPixels = image.bits();
    qThresholdedImage = QImage(image.width(), image.height(), QImage::Format_Grayscale8);
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

    int kernel2[49] = {32, 32, 32, 32, 32, 32, 32,
                       32, 16, 16, 16, 16, 16, 32,
                       32, 16,  8,  8,  8, 16, 32,
                       32, 16,  8,  1,  8, 16, 32,
                       32, 16,  8,  8,  8, 16, 32,
                       32, 16, 16, 16, 16, 16, 32,
                       32, 32, 32, 32, 32, 32, 32};

    int kernel3_width = 3;
    int kernel3_height = 3;
    int stride3_x = 1;
    int stride3_y = 1;
    int kernel3[9] = {0, 1, 0,
                      1, 1, 1,
                      0, 1, 0};


    int sizeBlock3 = kernel3_width * kernel3_height;
    uchar* block3 = (uchar*)malloc(sizeBlock3 * sizeof(uchar));

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
    if(opMorpho == GSEROSION){
        for (int y = 3; y < image.height()-3; y++) {
            for (int x = 3; x < image.width()-3; x++) {

                for (int kernel_y = 0; kernel_y < kernel_height; kernel_y++) {
                    for (int kernel_x = 0; kernel_x < kernel_width; kernel_x++) {
                        block[kernel_x + (kernel_y * kernel_width)] = savedImage.pixelColor((x - stride_x) + kernel_x, (y  - stride_y) + kernel_y).value();
                    }
                    int min = block[0];
                    for (int i = 0; i < sizeBlock; i++) {
                        if(block[i] < min && kernel[i]){
                            min = block[i];
                        }
                    }
                    morphologicalPixels[x + (y * image.width())] = min;
                }
                free(block);
            }
        }
    }
    if(opMorpho == GSDILATE){
        for (int y = 3; y < image.height()-3; y++) {
            for (int x = 3; x < image.width()-3; x++) {

                for (int kernel_y = 0; kernel_y < kernel_height; kernel_y++) {
                    for (int kernel_x = 0; kernel_x < kernel_width; kernel_x++) {
                        block[kernel_x + (kernel_y * kernel_width)] = savedImage.pixelColor((x - stride_x) + kernel_x, (y  - stride_y) + kernel_y).value();
                    }

                    int max  = block[0];
                    for (int i = 0; i < sizeBlock; i++) {
                        if(block[i] > max && kernel[i]){
                            max = block[i];
                        }
                    }
                    morphologicalPixels[x + (y * image.width())] = max;
                }
                free(block);
            }
        }
    }

    if(opMorpho == GRADIENT){
        for (int y = 1; y < image.height()-1; y++) {
            for (int x = 1; x < image.width()-1; x++) {

                for (int kernel_y = 0; kernel_y < kernel3_height; kernel_y++) {
                    for (int kernel_x = 0; kernel_x < kernel3_width; kernel_x++) {
                        block3[kernel_x + (kernel_y * kernel3_width)] = savedImage.pixelColor((x - stride3_x) + kernel_x, (y  - stride3_y) + kernel_y).value();
                    }

                    int max  = block3[0];
                    int min = block3[0];
                    for (int i = 0; i < sizeBlock3; i++) {
                        if(block3[i] > max && kernel3[i]){
                            max = block3[i];
                        }
                        if(block3[i] < min && kernel3[i]){
                            min = block3[i];
                        }
                    }
                    morphologicalPixels[x + (y * image.width())] = (max - min);
                }
                free(block3);
            }
        }
    }

    if(opMorpho == TOPHAT){
        //Imagen original - opening
        uchar* savedPixels = savedImage.bits();
        for (int y = 0; y < image.height(); y++) {
            for (int x = 0; x < image.width(); x++) {
                morphologicalPixels[x + (y * image.width())] = originalPixels[x + (y * image.width())] - savedPixels[x + (y * image.width())];
            }
        }
    }

    if(opMorpho == OTHER){
        //closure - imagen original
        uchar* savedPixels = savedImage.bits();
        for (int y = 1; y < image.height()-1; y++) {
            for (int x = 1; x < image.width()-1; x++) {
                morphologicalPixels[x + (y * image.width())] = savedPixels[x + (y * image.width())] - originalPixels[x + (y * image.width())];
            }
        }
    }
}

void morphological::saveImage(QImage img){
    this->savedImage = img;
}

void morphological::setOriginalImage(QImage img){
    this->originalPixels = img.bits();
}
