#include "metadatafile.h"
#include <QTextStream>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDataStream>
#include <QVector>
#include <QDebug>

MetadataFile::MetadataFile(QString path)
{
    this->path = path;
    rgb = NULL;
    hsv = NULL;
    yuv = NULL;
    metadata = NULL;
}

bool MetadataFile::read()
{
    QFile file(path);
    if(!file.open(QIODevice::ReadOnly))
        return NULL;
    QDataStream in(&file);

    quint8 r,g,b,h,s,v,y,u,val;

    RGB_Data *rgb = new RGB_Data();
    rgb->r = new QVector<int>();
    rgb->g = new QVector<int>();
    rgb->b = new QVector<int>();

    HSV_Data *hsv = new HSV_Data();
    hsv->h = new QVector<int>();
    hsv->s = new QVector<int>();
    hsv->v = new QVector<int>();

    YUV_Data *yuv = new YUV_Data();
    yuv->y = new QVector<int>();
    yuv->u = new QVector<int>();
    yuv->v = new QVector<int>();

    for (int i=0;i<imagePixels;i++) {
        in >> r;
        in >> g;
        in >> b;
        in >> h;
        in >> s;
        in >> v;
        in >> y;
        in >> u;
        in >> val;
        (*rgb->r)[i] = (int)r;
        (*rgb->g)[i] = (int)g;
        (*rgb->b)[i] = (int)b;
        (*hsv->h)[i] = (int)h;
        (*hsv->s)[i] = (int)s;
        (*hsv->v)[i] = (int)v;
        (*yuv->y)[i] = (int)y;
        (*yuv->u)[i] = (int)u;
        (*yuv->v)[i] = (int)val;
    }
    file.close();

    Metadata *metadata = new Metadata();

    metadata->setRGB(rgb);
    metadata->setHSV(hsv);
    metadata->setYUV(yuv);

    return true;
}

Metadata* MetadataFile::getMetadata (QString path)
{
    QFile file(path);
    if(!file.open(QIODevice::ReadOnly))
        return NULL;
    QDataStream in(&file);

    quint8 r,g,b,h,s,v,y,u,val;

    RGB_Data *rgb = new RGB_Data();
    rgb->r = new QVector<int>(imagePixels/(samplingValue*samplingValue), 0);
    rgb->g = new QVector<int>(imagePixels/(samplingValue*samplingValue), 0);
    rgb->b = new QVector<int>(imagePixels/(samplingValue*samplingValue), 0);

    HSV_Data *hsv = new HSV_Data();
    hsv->h = new QVector<int>(imagePixels/(samplingValue*samplingValue), 0);
    hsv->s = new QVector<int>(imagePixels/(samplingValue*samplingValue), 0);
    hsv->v = new QVector<int>(imagePixels/(samplingValue*samplingValue), 0);

    YUV_Data *yuv = new YUV_Data();
    yuv->y = new QVector<int>(imagePixels/(samplingValue*samplingValue), 0);
    yuv->u = new QVector<int>(imagePixels/(samplingValue*samplingValue), 0);
    yuv->v = new QVector<int>(imagePixels/(samplingValue*samplingValue), 0);

    for (int i=0;i<imagePixels/(samplingValue*samplingValue);i++) {
        in >> r;
        in >> g;
        in >> b;
        in >> h;
        in >> s;
        in >> v;
        in >> y;
        in >> u;
        in >> val;
        (*rgb->r)[i] = (int)r;
        (*rgb->g)[i] = (int)g;
        (*rgb->b)[i] = (int)b;
        (*hsv->h)[i] = (int)h;
        (*hsv->s)[i] = (int)s;
        (*hsv->v)[i] = (int)v;
        (*yuv->y)[i] = (int)y;
        (*yuv->u)[i] = (int)u;
        (*yuv->v)[i] = (int)val;
        if (samplingValue>8) {
            in.skipRawData(((samplingValue-8)/8)*9);
        }
    }
    file.close();

    Metadata *metadata = new Metadata();

    metadata->setRGB(rgb);
    metadata->setHSV(hsv);
    metadata->setYUV(yuv);

    return metadata;
}

RGB_Data* MetadataFile::getRGB (QString path)
{
    QFile file(path);
    if(!file.open(QIODevice::ReadOnly))
        return NULL;
    QDataStream in(&file);

    quint8 r,g,b;

    RGB_Data *rgb = new RGB_Data();
    rgb->r = new QVector<int>(imagePixels/(samplingValue*samplingValue), 0);
    rgb->g = new QVector<int>(imagePixels/(samplingValue*samplingValue), 0);
    rgb->b = new QVector<int>(imagePixels/(samplingValue*samplingValue), 0);

    for (int i=0;i<imagePixels/(samplingValue*samplingValue);i++) {
        in >> r;
        in >> g;
        in >> b;
        (*rgb->r)[i] = (int)r;
        (*rgb->g)[i] = (int)g;
        (*rgb->b)[i] = (int)b;
        in.skipRawData(6);
        if (samplingValue>8) {
            in.skipRawData(((samplingValue-8)/8)*9);
        }
    }
    file.close();
    return rgb;
}

HSV_Data* MetadataFile::getHSV (QString path)
{
    QFile file(path);
    if(!file.open(QIODevice::ReadOnly))
        return NULL;
    QDataStream in(&file);

    quint8 h,s,v;

    HSV_Data *hsv = new HSV_Data();
    hsv->h = new QVector<int>(imagePixels/(samplingValue*samplingValue), 0);
    hsv->s = new QVector<int>(imagePixels/(samplingValue*samplingValue), 0);
    hsv->v = new QVector<int>(imagePixels/(samplingValue*samplingValue), 0);

    in.skipRawData(3);
    for (int i=0;i<imagePixels/(samplingValue*samplingValue);i++) {
        in >> h;
        in >> s;
        in >> v;
        (*hsv->h)[i] = (int)h;
        (*hsv->s)[i] = (int)s;
        (*hsv->v)[i] = (int)v;
        in.skipRawData(6);
        if (samplingValue>8) {
            in.skipRawData(((samplingValue-8)/8)*9);
        }
    }
    file.close();
    return hsv;
}

YUV_Data* MetadataFile::getYUV (QString path)
{

    QFile file(path);
    if(!file.open(QIODevice::ReadOnly))
        return NULL;
    QDataStream in(&file);

    quint8 y,u,v;

    YUV_Data *yuv = new YUV_Data();
    yuv->y = new QVector<int>(imagePixels/(samplingValue*samplingValue), 0);
    yuv->u = new QVector<int>(imagePixels/(samplingValue*samplingValue), 0);
    yuv->v = new QVector<int>(imagePixels/(samplingValue*samplingValue), 0);

    in.skipRawData(6);
    for (int i=0;i<imagePixels/(samplingValue*samplingValue);i++) {
        in >> y;
        in >> u;
        in >> v;
        (*yuv->y)[i] = (int)y;
        (*yuv->u)[i] = (int)u;
        (*yuv->v)[i] = (int)v;
        in.skipRawData(6);
        if (samplingValue>8) {
            in.skipRawData(((samplingValue-8)/8)*9);
        }
    }
    file.close();
    return yuv;
}
