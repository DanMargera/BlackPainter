#ifndef PIDTOOLS_H
#define PIDTOOLS_H

#include <QImage>
#include <QVector>
#include "complex.h"

static const double nValue = 255; // VALOR USADO PRA NORMALIZAR OS RESULTADOS
static const int imagePixels = 98304; // número de pixels das imagens do banco de dados

struct RGB_Data
{
    QVector<int>* r;
    QVector<int>* g;
    QVector<int>* b;
    int xMax;
    int yMax;
};

struct HSV_Data
{
    QVector<int>* h;
    QVector<int>* s;
    QVector<int>* v;
};

struct YUV_Data
{
    QVector<int>* y;
    QVector<int>* u;
    QVector<int>* v;
};

struct CMYK_Data
{
    QVector<int>* c;
    QVector<int>* m;
    QVector<int>* y;
    QVector<int>* k;
};

struct YUVpixel
{
    qreal y; // vai de [0 a 1]
    qreal u; // vai de [-uMax a uMax]
    qreal v; // vai de [-vMax a vMax]
};

struct HSVpixel
{
    qreal h; // angulo 0 a 359
    qreal s; // saturação em %
    qreal v; // value em %
};

struct CMYKpixel
{
    qreal c;
    qreal m;
    qreal y;
    qreal k;
};

struct RGBpixel
{
    int r;
    int g;
    int b;
};

struct ImageCell
{
    QString path;
    qreal distance;
};

class PIDTools
{
public:


    PIDTools(QImage* image) : image(image) {}


    static QImage negative(QImage image);
    static RGB_Data*    rgbHistogram(QImage image);
    static RGB_Data*    rgbData(QImage image);
    static HSV_Data*      hsvData(QImage image);
    static YUV_Data*      yuvData(QImage image);
    static CMYK_Data* cmykHistogram(QImage image);
    static CMYKpixel   rgb2cmyk(QRgb rgb);
    static RGBpixel    rgb(QRgb rgb);
    static HSVpixel    rgb2hsv(QRgb rgb);
    static YUVpixel    rgb2yuv(QRgb rgb);
    static QImage gray_scale(QImage image);
    static int rgb2gray_scale(QRgb rgb);
    static QImage convolution(QImage image);
    static QImage convolution_GS(QImage image);
    static QImage threshold(QImage image, int value);
    static QImage RGB_Level(QImage image, qreal low, qreal high);
    static QImage brightnessContrast(QImage image, qreal brightness, qreal contrast);
    static QImage fft(QImage image);
    static QImage ifft(QImage image);



private:
    QImage* image;

};

#endif // PIDTOOLS_H
