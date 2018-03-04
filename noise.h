#ifndef NOISE_H
#define NOISE_H
#include <QImage>


enum Filters{
    MEAN,
    MEDIAN,
    GAUSSIAN
};

class noise
{
public:
    noise();
    void smoothing(Filters,QImage);
    QImage getDenoisingImage() {return qDenoisingImage;}

private:
    QImage qDenoisingImage;

};

#endif // NOISE_H
