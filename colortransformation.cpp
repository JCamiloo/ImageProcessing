#include "colortransformation.h"
#include "QImageWriter"

ColorTransformation::ColorTransformation()
{

}

void ColorTransformation::RGBtoHSL(QImage image){

    HSLImage = QImage(image.width(), image.height(), image.format());
    red = QImage(image.width(), image.height(), image.format());
    green = QImage(image.width(), image.height(), image.format());
    blue = QImage(image.width(), image.height(), image.format());

    for(int y = 0; y < image.height(); y++){
        for (int x = 0; x < image.width(); x++){

            QColor clrcurrent(image.pixel(x,y));

            //Los valores RGB deben estar entre 0 y 255
            //Los valores HSL deben estar entre 0 y 1

            qreal var_R = (qreal) clrcurrent.red() / 255;
            qreal var_G = (qreal) clrcurrent.green() / 255;
            qreal var_B = (qreal) clrcurrent.blue() / 255;

            //printf("var_R: %f - var_G %f - var_B %f \n", var_R, var_G, var_B);

            qreal var_Min = std::min(std::min(var_R, var_G), var_B);
            qreal var_Max = std::max(std::max(var_R, var_G), var_B);
            qreal del_Max = var_Max - var_Min;

            qreal H = 0;
            qreal S = 0;
            qreal L = (var_Max + var_Min) / 2;

            if(del_Max == 0){
                H = 0;
                S = 0;
            }
            else{
                if(L < 0.5){
                    S = del_Max / (var_Max + var_Min);
                }
                else{
                    S = del_Max / (2 - var_Max - var_Min);
                }

                qreal del_R = ((( var_Max - var_R ) / 6) + (del_Max / 2)) / del_Max;
                qreal del_G = ((( var_Max - var_G ) / 6) + (del_Max / 2)) / del_Max;
                qreal del_B = ((( var_Max - var_B ) / 6) + (del_Max / 2)) / del_Max;

                if(var_R == var_Max){
                    H = del_B - del_G;
                }
                else if(var_G == var_Max){
                    H = (1 / 3.0f) + del_R - del_B;
                }
                else if(var_B == var_Max){
                    H = (2 / 3.0f) + del_G - del_R;
                }

                if(H < 0){
                    H += 1;
                }

                if(H > 1){
                    H -= 1;
                }
            }
            //printf("var_H: %f - var_S %f - var_L %f \n", H, S, L);
            QColor color;
            color.setHslF(H,S,L);
            HSLImage.setPixelColor(x,y,color);
            int r = H * 225;
            int g = S * 255;
            int b = L * 255;
            //printf("var r: %d - var g %d - var b %d \n", r, g, b);
            red.setPixel(x, y, qRgb(r, 0, 0));
            green.setPixel(x, y, qRgb(0, g, 0));
            blue.setPixel(x, y, qRgb(0, 0, b));
        }
    }
    //QImageWriter writerH("C:/Users/sony/Desktop/HSL-H.jpg");
    //QImageWriter writerS("C:/Users/sony/Desktop/HSL-S.jpg");
    //QImageWriter writerL("C:/Users/sony/Desktop/HSL-L.jpg");
    //writerH.write(red);
    //writerS.write(green);
    //writerL.write(blue);
}

void ColorTransformation::RGBtoHSV(QImage image){

    HSVImage = QImage(image.width(), image.height(), image.format());
    red = QImage(image.width(), image.height(), image.format());
    green = QImage(image.width(), image.height(), image.format());
    blue = QImage(image.width(), image.height(), image.format());

    for(int y = 0; y < image.height(); y++){
        for (int x = 0; x < image.width(); x++){

            QColor clrcurrent(image.pixel(x,y));

            //Los valores RGB deben estar entre 0 y 255
            //Los valores HSL deben estar entre 0 y 1

            qreal var_R = (qreal) clrcurrent.red() / 255;
            qreal var_G = (qreal) clrcurrent.green() / 255;
            qreal var_B = (qreal) clrcurrent.blue() / 255;

            //printf("var_R: %f - var_G %f - var_B %f \n", var_R, var_G, var_B);

            qreal var_Min = std::min(std::min(var_R, var_G), var_B);
            qreal var_Max = std::max(std::max(var_R, var_G), var_B);
            qreal del_Max = var_Max - var_Min;

            qreal H = 0;
            qreal S = 0;
            qreal V = var_Max;

            if(del_Max == 0){
                H = 0;
                S = 0;
            }
            else{
                S = del_Max / var_Max;

                qreal del_R = ((( var_Max - var_R ) / 6) + (del_Max / 2)) / del_Max;
                qreal del_G = ((( var_Max - var_G ) / 6) + (del_Max / 2)) / del_Max;
                qreal del_B = ((( var_Max - var_B ) / 6) + (del_Max / 2)) / del_Max;

                if(var_R == var_Max){
                    H = del_B - del_G;
                }
                else if(var_G == var_Max){
                    H = (1/3.0f) + del_R - del_B;
                }
                else if(var_B == var_Max){
                    H = (2/3.0f) + del_G - del_R;
                }

                if (H < 0) {
                    H += 1;
                }

                if(H > 1){
                    H -= 1;
                }
            }

            //printf("var_H: %f - var_S %f - var_V %f \n", H, S, V);
            QColor color;
            color.setHsvF(H,S,V);
            HSVImage.setPixelColor(x,y,color);
            int r = H * 225;
            int g = S * 255;
            int b = V * 255;
            //printf("var r: %d - var g %d - var b %d \n", r, g, b);
            red.setPixel(x, y, qRgb(r, 0, 0));
            green.setPixel(x, y, qRgb(0, g, 0));
            blue.setPixel(x, y, qRgb(0, 0, b));
        }
    }
    //QImageWriter writerH("C:/Users/sony/Desktop/HSV-H.jpg");
    //QImageWriter writerS("C:/Users/sony/Desktop/HSV-S.jpg");
    //QImageWriter writerV("C:/Users/sony/Desktop/HSV-V.jpg");
    //writerH.write(red);
    //writerS.write(green);
    //writerV.write(blue);
}
