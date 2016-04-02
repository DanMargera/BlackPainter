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
    if(!file.open(QFile::ReadOnly | QFile::Text))
        return false;
    QTextStream in(&file);

    QJsonDocument jsonDocument =  QJsonDocument::fromJson(in.readAll().toUtf8());

    file.close();

    QJsonObject jsonObject;

    QJsonObject jsonObjectRGB = jsonDocument.object().take("RGB").toObject();
    QJsonArray jsonArrayRGB_r = jsonObjectRGB.take("R").toArray();
    QJsonArray jsonArrayRGB_g = jsonObjectRGB.take("G").toArray();
    QJsonArray jsonArrayRGB_b = jsonObjectRGB.take("B").toArray();

    QJsonObject jsonObjectHSV = jsonDocument.object().take("HSV").toObject();
    QJsonArray jsonArrayHSV_h  = jsonObjectHSV.take("H").toArray();
    QJsonArray jsonArrayHSV_s  = jsonObjectHSV.take("S").toArray();
    QJsonArray jsonArrayHSV_v  = jsonObjectHSV.take("V").toArray();

    QJsonObject jsonObjectYUV = jsonDocument.object().take("YUV").toObject();
    QJsonArray jsonArrayYUV_y = jsonObjectYUV.take("Y").toArray();
    QJsonArray jsonArrayYUV_u = jsonObjectYUV.take("U").toArray();
    QJsonArray jsonArrayYUV_v = jsonObjectYUV.take("V").toArray();

    rgb = new RGB_Data();
    rgb->r = new QVector<int>();
    rgb->g = new QVector<int>();
    rgb->b = new QVector<int>();
    for(int i = 0; i < jsonArrayRGB_r.size(); i++)
    {
        (*rgb->r)[i] = jsonArrayRGB_r.at(i).toInt();
        (*rgb->g)[i] = jsonArrayRGB_g.at(i).toInt();
        (*rgb->b)[i] = jsonArrayRGB_b.at(i).toInt();
    }

    hsv = new HSV_Data();
    hsv->h = new QVector<int>();
    hsv->s = new QVector<int>();
    hsv->v = new QVector<int>();
    for(int i = 0; i < jsonArrayHSV_h.size(); i++)
    {
        (*hsv->h)[i] = jsonArrayHSV_h.at(i).toInt();
        (*hsv->s)[i] = jsonArrayHSV_s.at(i).toInt();
        (*hsv->v)[i] = jsonArrayHSV_v.at(i).toInt();
    }

    yuv = new YUV_Data();
    yuv->y = new QVector<int>();
    yuv->u = new QVector<int>();
    yuv->v = new QVector<int>();
    for(int i = 0; i < jsonArrayYUV_y.size(); i++)
    {
        (*yuv->y)[i] = jsonArrayYUV_y.at(i).toInt();
        (*yuv->u)[i] = jsonArrayYUV_u.at(i).toInt();
        (*yuv->v)[i] = jsonArrayYUV_v.at(i).toInt();
    }

    metadata = new Metadata();

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
    rgb->r = new QVector<int>(imagePixels, 0);
    rgb->g = new QVector<int>(imagePixels, 0);
    rgb->b = new QVector<int>(imagePixels, 0);

    for (int i=0;i<imagePixels;i++) {
        in >> r;
        in >> g;
        in >> b;
        (*rgb->r)[i] = (int)r;
        (*rgb->g)[i] = (int)g;
        (*rgb->b)[i] = (int)b;
        in.skipRawData(6);
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
    hsv->h = new QVector<int>();
    hsv->s = new QVector<int>();
    hsv->v = new QVector<int>();

    in.skipRawData(3);
    for (int i=0;i<imagePixels;i++) {
        in >> h;
        in >> s;
        in >> v;
        (*hsv->h)[i] = (int)h;
        (*hsv->s)[i] = (int)s;
        (*hsv->v)[i] = (int)v;
        in.skipRawData(6);
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
    yuv->y = new QVector<int>();
    yuv->u = new QVector<int>();
    yuv->v = new QVector<int>();

    in.skipRawData(6);
    for (int i=0;i<imagePixels;i++) {
        in >> y;
        in >> u;
        in >> v;
        (*yuv->y)[i] = (int)y;
        (*yuv->u)[i] = (int)u;
        (*yuv->v)[i] = (int)v;
        in.skipRawData(6);
    }
    file.close();
    return yuv;
}
