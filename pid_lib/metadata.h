#ifndef METADATA_H
#define METADATA_H

#include <QImage>
#include "pidtools.h"

enum ComparisonTypes {
    Rgb, Hsv, Yuv, Sampling
};
enum MeasureTypes {
    Manhattan, Euclidean, Chess, Cosine
};

class Comparable
{
public:
    Comparable(RGB_Data* rgb);
    Comparable(HSV_Data* hsv);
    Comparable(YUV_Data* yuv);
    Comparable(Sampling_Data* sData);

    int dimensions;
    QVector<int>* v1;
    QVector<int>* v2;
    QVector<int>* v3;
};

class Metadata
{

public:
    Metadata();
    void setRGB(RGB_Data* rgbData) { rgb = rgbData; }
    void setHSV(HSV_Data* hsvData) { hsv = hsvData; }
    void setYUV(YUV_Data* yuvData) { yuv = yuvData; }
    void setSampling(Sampling_Data* sData) { samplingData = sData; }

    void generateRGB(QImage image);
    void generateYUV(QImage image);
    void generateHSV(QImage image);
    void generateSampling(QImage image);
    qreal compareTo(Metadata* m, int comparisonType, int measureType);

private:
    qreal manhattanDistance(Comparable* c1, Comparable* c2);
    qreal euclideanDistance(Comparable* c1, Comparable* c2);
    qreal chessDistance(Comparable* c1, Comparable* c2);
    qreal cosineDistance(Comparable* c1, Comparable* c2);

    RGB_Data* rgb;
    HSV_Data* hsv;
    YUV_Data* yuv;
    Sampling_Data* samplingData;
};

#endif // METADATA_H
