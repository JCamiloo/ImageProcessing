#include "noise.h"

int gaussian3x3[3][3] = {{1,2,1},{2,4,2},{1,2,1}};

noise::noise()
{

}

void noise::smoothing(Filters filter, QImage image){
    qDenoisingImage = QImage(image.width(),image.height(),image.format());
    uchar* denoisingPixels = qDenoisingImage.bits();

    if(filter==MEAN){
        for (int y = 1; y < image.height()-1; y++) {
            for (int x = 1; x < image.width()-1; x++) {
                int average = 0;
                average += image.pixelColor(x-1,y-1).value();
                average += image.pixelColor(x,y-1).value();
                average += image.pixelColor(x+1,y-1).value();
                average += image.pixelColor(x-1,y).value();
                average += image.pixelColor(x-1,y-1).value();
                average += image.pixelColor(x+1,y).value();
                average += image.pixelColor(x-1,y+1).value();
                average += image.pixelColor(x,y+1).value();
                average += image.pixelColor(x+1,y+1).value();

                denoisingPixels[x + (y * image.width())] = (int) average / 9;
            }
        }
    }
    else if(filter == MEDIAN){
        for(int y = 1; y < image.height() - 1; y++){
            for (int x = 1; x < image.width() - 1; x++) {
                QVector<int> block;
                block.append(image.pixelColor(x-1,y-1).value());
                block.append(image.pixelColor(x,y-1).value());
                block.append(image.pixelColor(x+1,y-1).value());
                block.append(image.pixelColor(x-1,y).value());
                block.append(image.pixelColor(x-1,y-1).value());
                block.append(image.pixelColor(x+1,y).value());
                block.append(image.pixelColor(x-1,y+1).value());
                block.append(image.pixelColor(x,y+1).value());
                block.append(image.pixelColor(x+1,y+1).value());

                qSort(block);

                denoisingPixels[x + (y * image.width())] = block.at(5);
            }
        }
    }

    else if(filter == GAUSSIAN){
        for (int y = 2; y < image.height()-2; y++) {
            for (int x = 2; x < image.width()-2; x++) {
                int gaussian = 0;
                gaussian += image.pixelColor(x-1,y-1).value() * gaussian3x3[0][0];
                gaussian += image.pixelColor(x,y-1).value() *  gaussian3x3[1][0];
                gaussian += image.pixelColor(x+1,y-1).value()* gaussian3x3[2][0];
                gaussian += image.pixelColor(x-1,y).value()* gaussian3x3[0][1];
                gaussian += image.pixelColor(x-1,y-1).value()* gaussian3x3[1][1];
                gaussian += image.pixelColor(x+1,y).value()* gaussian3x3[2][1];
                gaussian += image.pixelColor(x-1,y+1).value()* gaussian3x3[0][2];
                gaussian += image.pixelColor(x,y+1).value()* gaussian3x3[1][2];
                gaussian += image.pixelColor(x+1,y+1).value()* gaussian3x3[2][2];

                denoisingPixels[x + (y * image.width())] = (int)gaussian / 16;
            }
        }
    }
}
