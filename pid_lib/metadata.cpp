#include "metadata.h"

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

Comparable::Comparable(Sampling_Data *sData)
{
    v1 = sData->s;
    dimensions = 1;
}

Metadata::Metadata()
{

}

void Metadata::generateRGB(QImage image)
{
    rgb = PIDTools::rgbHistogram(image);
}

void Metadata::generateHSV(QImage image)
{
    hsv = PIDTools::hsvHistogram(image);
}

void Metadata::generateYUV(QImage image)
{
    yuv = PIDTools::yuvHistogram(image);
}

void Metadata::generateSampling(QImage image)
{
    samplingData = PIDTools::samplingHistogram(image);
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
    case Sampling:
        switch(measureType) {
        case Manhattan:
            return manhattanDistance(new Comparable(samplingData), new Comparable(m->samplingData));
        case Euclidean:
            return euclideanDistance(new Comparable(samplingData), new Comparable(m->samplingData));
        case Chess:
            return chessDistance(new Comparable(samplingData), new Comparable(m->samplingData));
        case Cosine:
            return cosineDistance(new Comparable(samplingData), new Comparable(m->samplingData));
        }
        break;
    default:
        return 0;
    }
}

qreal Metadata::manhattanDistance(Comparable *c1, Comparable *c2)
{
    int distance = 0;
    switch(c1->dimensions) {
    case 3:
        for (int i=0;i<nValue;i++) {
            distance += ABS(((*c1->v1)[i]-(*c2->v1)[i]));
            distance += ABS(((*c1->v2)[i]-(*c2->v2)[i]));
            distance += ABS(((*c1->v3)[i]-(*c2->v3)[i]));
        }
        break;
    case 2:
        for (int i=0;i<nValue;i++) {
            distance += ABS(((*c1->v1)[i]-(*c2->v1)[i]));
            distance += ABS(((*c1->v2)[i]-(*c2->v2)[i]));
        }
    case 1:
        for (int i=0;i<nValue;i++) {
            distance += ABS(((*c1->v1)[i]-(*c2->v1)[i]));
        }
    }
    return distance;
}

qreal Metadata::euclideanDistance(Comparable *c1, Comparable *c2)
{

}

qreal Metadata::chessDistance(Comparable *c1, Comparable *c2)
{

}

qreal Metadata::cosineDistance(Comparable *c1, Comparable *c2)
{

}

