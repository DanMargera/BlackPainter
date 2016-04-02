#include "metadata.h"
#include <QtMath>

#define ABS(x) ((x) > 0)?(x):-(x)

Comparable::Comparable(RGB_Data *rgb)
{
    v1 = rgb->r;
    v2 = rgb->g;
    v3 = rgb->b;
    dimensions = 3;
}

Comparable::Comparable(HSV_Data *hsv)
{
    v1 = hsv->h;
    v2 = hsv->s;
    v3 = hsv->v;
    dimensions = 3;
}

Comparable::Comparable(YUV_Data *yuv)
{
    v1 = yuv->y;
    v2 = yuv->u;
    v3 = yuv->v;
    dimensions = 3;
}

Metadata::Metadata()
{

}

void Metadata::generateRGB(QImage image)
{
    rgb = PIDTools::rgbData(image);
}

void Metadata::generateHSV(QImage image)
{
    hsv = PIDTools::hsvData(image);
}

void Metadata::generateYUV(QImage image)
{
    yuv = PIDTools::yuvData(image);
}

qreal Metadata::compareTo(Metadata* m, int comparisonType, int measureType)
{
    switch(comparisonType) {
    case Rgb:
        switch(measureType) {
        case Manhattan:
            return manhattanDistance(new Comparable(rgb), new Comparable(m->rgb));
        case Euclidean:
            return euclideanDistance(new Comparable(rgb), new Comparable(m->rgb));
        case Chess:
            return chessDistance(new Comparable(rgb), new Comparable(m->rgb));
        case Cosine:
            return cosineDistance(new Comparable(rgb), new Comparable(m->rgb));
        }
    case Hsv:
        switch(measureType) {
        case Manhattan:
            return manhattanDistance(new Comparable(hsv), new Comparable(m->hsv));
        case Euclidean:
            return euclideanDistance(new Comparable(hsv), new Comparable(m->hsv));
        case Chess:
            return chessDistance(new Comparable(hsv), new Comparable(m->hsv));
        case Cosine:
            return cosineDistance(new Comparable(hsv), new Comparable(m->hsv));
        }
    case Yuv:
        switch(measureType) {
        case Manhattan:
            return manhattanDistance(new Comparable(yuv), new Comparable(m->yuv));
        case Euclidean:
            return euclideanDistance(new Comparable(yuv), new Comparable(m->yuv));
        case Chess:
            return chessDistance(new Comparable(yuv), new Comparable(m->yuv));
        case Cosine:
            return cosineDistance(new Comparable(yuv), new Comparable(m->yuv));
        }
    default:
        return 0;
    }
}

qreal Metadata::manhattanDistance(Comparable *c1, Comparable *c2)
{
    qreal distance = 0;
    switch(c1->dimensions) {
    case 3:
        for (int i=0;i<imagePixels;i++) {
            distance += ABS((*c1->v1)[i]-(*c2->v1)[i]);
            distance += ABS((*c1->v2)[i]-(*c2->v2)[i]);
            distance += ABS((*c1->v3)[i]-(*c2->v3)[i]);
        }
        break;
    case 2:
        for (int i=0;i<imagePixels;i++) {
            distance += ABS((*c1->v1)[i]-(*c2->v1)[i]);
            distance += ABS((*c1->v2)[i]-(*c2->v2)[i]);
        }
    case 1:
        for (int i=0;i<imagePixels;i++) {
            distance += ABS((*c1->v1)[i]-(*c2->v1)[i]);
        }
    }
}

qreal Metadata::euclideanDistance(Comparable *c1, Comparable *c2)
{
    qreal distance = 0;
    switch(c1->dimensions) {
    case 3:
        for (int i=0;i<imagePixels;i+=samplingValue) {
            distance += qPow((*c1->v1)[i]-(*c2->v1)[i] , 2);
            distance += qPow((*c1->v2)[i]-(*c2->v2)[i] , 2);
            distance += qPow((*c1->v3)[i]-(*c2->v3)[i] , 2);
        }
        break;
    case 2:
        for (int i=0;i<imagePixels;i+=samplingValue) {
            distance += qPow((*c1->v1)[i]-(*c2->v1)[i] , 2);
            distance += qPow((*c1->v2)[i]-(*c2->v2)[i] , 2);
        }
    case 1:
        for (int i=0;i<imagePixels;i+=samplingValue) {
            distance += qPow((*c1->v1)[i]-(*c2->v1)[i] , 2);
        }
    }
    return qSqrt(distance);
}

qreal Metadata::chessDistance(Comparable *c1, Comparable *c2)
{
    qreal distance = 0;
    switch(c1->dimensions) {
    case 3:
        for (int i=0;i<imagePixels;i+=samplingValue) {
            distance += qMax(qMax(ABS((*c1->v1)[i]-(*c2->v1)[i]), ABS((*c1->v2)[i]-(*c2->v2)[i])), ABS((*c1->v3)[i]-(*c2->v3)[i]));
        }
        break;
    case 2:
        for (int i=0;i<imagePixels;i+=samplingValue) {
            distance += qMax(ABS((*c1->v1)[i]-(*c2->v1)[i]), ABS((*c1->v2)[i]-(*c2->v2)[i]));
        }
    case 1:
        for (int i=0;i<imagePixels;i+=samplingValue) {
            distance += ABS(((*c1->v1)[i]-(*c2->v1)[i]));
        }
    }
    return distance;
}

qreal Metadata::cosineDistance(Comparable *c1, Comparable *c2)
{
    Q_UNUSED(c1)
    Q_UNUSED(c2)
}

