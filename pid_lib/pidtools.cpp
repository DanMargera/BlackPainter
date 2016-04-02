#include "metadata.h"
#include <QColor>
#include <cmath>
#include <QDebug>

const double wr = 0.299;
const double wb = 0.114;
const double wg = 1-wr-wb;
const double uMax = 0.436;
const double vMax = 0.615;

RGB_Data* PIDTools::rgbHistogram(QImage image)
{
    RGB_Data* vector = new RGB_Data();
    vector->r = new QVector<int>((int)nValue+1,0);
    vector->g = new QVector<int>((int)nValue+1,0);
    vector->b = new QVector<int>((int)nValue+1,0);
    vector->yMax = 0;
    vector->xMax = 255;
    RGBpixel rgbPixel;

    for(int x = 0; x < image.size().width(); x++)
        for(int y = 0; y < image.size().height(); y++)
        {
            rgbPixel = rgb(image.pixel(x,y));
            (*vector->r)[(int)(rgbPixel.r*nValue/255.0)]++;
            (*vector->g)[(int)(rgbPixel.g*nValue/255.0)]++;
            (*vector->b)[(int)(rgbPixel.b*nValue/255.0)]++;
        }

    for(int i = 0; i < (int)nValue+1; i++)
    {
        if((*vector->r)[i] > vector->yMax)
            vector->yMax = (*vector->r)[i];
        if((*vector->g)[i] > vector->yMax)
            vector->yMax = (*vector->g)[i];
        if((*vector->b)[i] > vector->yMax)
            vector->yMax = (*vector->b)[i];
    }

    return vector;
}

RGB_Data* PIDTools::rgbData(QImage image)
{
    RGB_Data* vector = new RGB_Data();
    vector->r = new QVector<int>(imagePixels/(samplingValue*samplingValue),0);
    vector->g = new QVector<int>(imagePixels/(samplingValue*samplingValue),0);
    vector->b = new QVector<int>(imagePixels/(samplingValue*samplingValue),0);
    RGBpixel rgbPixel;
    int i = 0;
    for(int x = 0; x < image.size().width(); x+=samplingValue)
        for(int y = 0; y < image.size().height(); y+=samplingValue)
        {
            rgbPixel = rgb(image.pixel(x,y));
            (*vector->r)[i] = (int)(rgbPixel.r*nValue/255.0);
            (*vector->g)[i] = (int)(rgbPixel.g*nValue/255.0);
            (*vector->b)[i] = (int)(rgbPixel.b*nValue/255.0);
            i++;
        }

    return vector;
}

HSV_Data* PIDTools::hsvData(QImage image)
{
    HSV_Data* data = new HSV_Data();
    data->h = new QVector<int>(imagePixels/(samplingValue*samplingValue),0);
    data->s = new QVector<int>(imagePixels/(samplingValue*samplingValue),0);
    data->v = new QVector<int>(imagePixels/(samplingValue*samplingValue),0);
    HSVpixel hsvPixel;
    int i = 0;
    for(int x = 0; x < image.size().width(); x+=samplingValue)
        for(int y = 0; y < image.size().height(); y+=samplingValue)
        {
            hsvPixel = rgb2hsv(image.pixel(x,y));
            (*data->h)[i] = (int)((hsvPixel.h*nValue)/360.0);
            (*data->s)[i] = (int)(hsvPixel.s*nValue);
            (*data->v)[i] = (int)(hsvPixel.v*nValue);
            i++;
        }

    return data;
}

YUV_Data* PIDTools::yuvData(QImage image)
{
    YUV_Data* data = new YUV_Data();
    data->y = new QVector<int>(imagePixels/(samplingValue*samplingValue),0);
    data->u = new QVector<int>(imagePixels/(samplingValue*samplingValue),0);
    data->v = new QVector<int>(imagePixels/(samplingValue*samplingValue),0);
    YUVpixel yuvPixel;
    int i = 0;
    for(int x = 0; x < image.size().width(); x+=samplingValue)
        for(int y = 0; y < image.size().height(); y+=samplingValue)
        {
            yuvPixel = rgb2yuv(image.pixel(x,y));
            (*data->y)[i] = (int)(yuvPixel.y*nValue);
            (*data->u)[i] = (int)(yuvPixel.u*nValue);
            (*data->v)[i] = (int)(yuvPixel.v*nValue);
            i++;
        }

    return data;
}

CMYK_Data* PIDTools::cmykHistogram(QImage image)
{
    CMYK_Data* vector = new CMYK_Data;
    vector->c = new QVector<int>(1000,0);
    vector->m = new QVector<int>(1000,0);
    vector->y = new QVector<int>(1000,0);
    vector->k = new QVector<int>(1000,0);

    for(int x = 0; x < image.size().width(); x++)
        for(int y = 0; y < image.size().height(); y++)
        {
            (*vector->c)[(int)rgb2cmyk(image.pixel(x,y)).c*1000.0]++;
            (*vector->m)[(int)rgb2cmyk(image.pixel(x,y)).m*1000.0]++;
            (*vector->y)[(int)rgb2cmyk(image.pixel(x,y)).y*1000.0]++;
            (*vector->k)[(int)rgb2cmyk(image.pixel(x,y)).k*1000.0]++;

        }
    return vector;
}

YUVpixel PIDTools::rgb2yuv(QRgb rgb)
{
    YUVpixel yuv;
    qreal r = (rgb >> 16)&0xff;
    qreal g = (rgb >>  8)&0xff;
    qreal b = rgb&0xff;

    r /= 255.0;
    g /= 255.0;
    b /= 255.0;

    // formula da wikipedia pra SDTV (pra hdtv muda as constantes wr e wb)
    yuv.y = (wr*r) + (wg*g) + (wb*b);
    yuv.u = uMax* ((b-yuv.y)/(1-wb));
    yuv.u += uMax;
    yuv.v = vMax* ((r-yuv.y)/(1-wr));
    yuv.v += vMax;
    yuv.v /= (2*vMax);

    return yuv;
}

HSVpixel PIDTools::rgb2hsv(QRgb rgb)
{
    HSVpixel hsv;
    qreal r = (rgb >> 16)&0xff;
    qreal g = (rgb >>  8)&0xff;
    qreal b = rgb&0xff;

    r /= 255.0;
    g /= 255.0;
    b /= 255.0;

    double min, max, delta;

    min = r < g ? r : g;
    min = min  < b ? min  : b;

    max = r > g ? r : g;
    max = max  > b ? max  : b;


    hsv.v = max;  // v
    delta = max - min;
    if (delta < 0.00001)
    {
        hsv.s = 0;
        hsv.h = 0; // undefined, maybe nan?
        return hsv;
    }
    if (max > 0.0) { // NOTE: if Max is == 0, this divide would cause a crash
        hsv.s = (delta / max);     // s
    } else {
        // if max is 0, then r = g = b = 0
            // s = 0, v is undefined
        hsv.s = 0.0;
        hsv.h = NAN;                            // its now undefined
        return hsv;
    }
    if (r >= max)                           // > is bogus, just keeps compilor happy
        hsv.h = ( g - b ) / delta;        // between yellow & magenta
    else if (g >= max)
        hsv.h = 2.0 + ( b - r ) / delta;  // between cyan & yellow
    else
        hsv.h = 4.0 + ( r - g ) / delta;  // between magenta & cyan

    hsv.h *= 60.0;                              // degrees

    if( hsv.h < 0.0 )
        hsv.h += 360.0;

    return hsv;
}

CMYKpixel PIDTools::rgb2cmyk(QRgb rgb)
{
    CMYKpixel cmyk;

    qreal r = (rgb >> 16)&0xff;
    qreal g = (rgb >>  8)&0xff;
    qreal b = rgb&0xff;

    cmyk.k = 1 - (r > g ? (r > b ? r : b) : (g > b ? g : b));

    cmyk.c = (1-r-cmyk.k)/(1-cmyk.k);
    cmyk.m = (1-g-cmyk.k)/(1-cmyk.k);
    cmyk.y = (1-b-cmyk.k)/(1-cmyk.k);

    return cmyk;
}

RGBpixel PIDTools::rgb(QRgb rgb)
{
    RGBpixel rgbpix;

    rgbpix.r = (rgb >> 16)&0xff;
    rgbpix.g = (rgb >>  8)&0xff;
    rgbpix.b = rgb&0xff;

    return rgbpix;
}

int PIDTools::rgb2gray_scale(QRgb rgb)
{
    int a = (rgb >> 24)&0xff;
    int r = (rgb >> 16)&0xff;
    int g = (rgb >>  8)&0xff;
    int b = rgb&0xff;

    int bw = r*0.3+g*0.59+b*0.11;
    a = (a << 8) + bw;
    a = (a << 8) + bw;
    a = (a << 8) + bw;
    return a;
}

QImage PIDTools::negative(QImage image)
{
    for(int x = 0; x < image.size().width(); x++)
        for(int y = 0; y < image.size().height(); y++)
            image.setPixel(x,y,(~image.pixel(x,y))|0xff000000);
    return image;
}

QImage PIDTools::gray_scale(QImage image)
{
    for(int x = 0; x < image.size().width(); x++)
        for(int y = 0; y < image.size().height(); y++)
            image.setPixel(x,y,rgb2gray_scale(image.pixel(x,y)));
    return image;
}

QImage PIDTools::convolution(QImage image)
{
    QImage result(image.size(),image.format());
    QVector <int> kernel;
    /*
    kernel << a << b << c
           << d << e << f
           << g << h << i;
    */

    kernel << 1 << 0 << -1
           << 1 << 0 << -1
           << 1 << 0 << -1;

    RGBpixel pixel;
    pixel.r = 0;
    pixel.g = 0;
    pixel.b = 0;


    for(int x = 1; x < image.size().width()-1; x++)
        for(int y = 1; y < image.size().height()-1; y++)
        {
            pixel.r += rgb(image.pixel(x-1,y-1)).r*kernel[8];
            pixel.r += rgb(image.pixel(x  ,y-1)).r*kernel[7];
            pixel.r += rgb(image.pixel(x+1,y-1)).r*kernel[6];
            pixel.r += rgb(image.pixel(x-1,y  )).r*kernel[5];
            pixel.r += rgb(image.pixel(x  ,y  )).r*kernel[4];
            pixel.r += rgb(image.pixel(x+1,y  )).r*kernel[3];
            pixel.r += rgb(image.pixel(x-1,y+1)).r*kernel[2];
            pixel.r += rgb(image.pixel(x  ,y+1)).r*kernel[1];
            pixel.r += rgb(image.pixel(x+1,y+1)).r*kernel[0];

            pixel.g += rgb(image.pixel(x-1,y-1)).g*kernel[8];
            pixel.g += rgb(image.pixel(x  ,y-1)).g*kernel[7];
            pixel.g += rgb(image.pixel(x+1,y-1)).g*kernel[6];
            pixel.g += rgb(image.pixel(x-1,y  )).g*kernel[5];
            pixel.g += rgb(image.pixel(x  ,y  )).g*kernel[4];
            pixel.g += rgb(image.pixel(x+1,y  )).g*kernel[3];
            pixel.g += rgb(image.pixel(x-1,y+1)).g*kernel[2];
            pixel.g += rgb(image.pixel(x  ,y+1)).g*kernel[1];
            pixel.g += rgb(image.pixel(x+1,y+1)).g*kernel[0];

            pixel.b += rgb(image.pixel(x-1,y-1)).b*kernel[8];
            pixel.b += rgb(image.pixel(x  ,y-1)).b*kernel[7];
            pixel.b += rgb(image.pixel(x+1,y-1)).b*kernel[6];
            pixel.b += rgb(image.pixel(x-1,y  )).b*kernel[5];
            pixel.b += rgb(image.pixel(x  ,y  )).b*kernel[4];
            pixel.b += rgb(image.pixel(x+1,y  )).b*kernel[3];
            pixel.b += rgb(image.pixel(x-1,y+1)).b*kernel[2];
            pixel.b += rgb(image.pixel(x  ,y+1)).b*kernel[1];
            pixel.b += rgb(image.pixel(x+1,y+1)).b*kernel[0];

            result.setPixel(x,y,QColor(
                                pixel.r < 0 ? 0 : pixel.r > 255 ? 255 : pixel.r,
                                pixel.g < 0 ? 0 : pixel.g > 255 ? 255 : pixel.g,
                                pixel.b < 0 ? 0 : pixel.b > 255 ? 255 : pixel.b)
                                .rgba());

            pixel.r = 0;
            pixel.g = 0;
            pixel.b = 0;
        }
    return result;
}

QImage PIDTools::convolution_GS(QImage image)
{
    image = gray_scale(image);
    QImage result(image.size(),image.format());
    QVector <int> kernel;
    /*
    kernel << a << b << c
           << d << e << f
           << g << h << i;
    */

    kernel << 1 << 0 << -1
           << 1 << 0 << -1
           << 1 << 0 << -1;

    int pixel = 0;


    for(int x = 1; x < image.size().width()-1; x++)
        for(int y = 1; y < image.size().height()-1; y++)
        {
            pixel += rgb(image.pixel(x-1,y-1)).r*kernel[8];
            pixel += rgb(image.pixel(x  ,y-1)).r*kernel[7];
            pixel += rgb(image.pixel(x+1,y-1)).r*kernel[6];
            pixel += rgb(image.pixel(x-1,y  )).r*kernel[5];
            pixel += rgb(image.pixel(x  ,y  )).r*kernel[4];
            pixel += rgb(image.pixel(x+1,y  )).r*kernel[3];
            pixel += rgb(image.pixel(x-1,y+1)).r*kernel[2];
            pixel += rgb(image.pixel(x  ,y+1)).r*kernel[1];
            pixel += rgb(image.pixel(x+1,y+1)).r*kernel[0];

            pixel = pixel < 0 ? 0 : pixel > 255 ? 255 : pixel;

            result.setPixel(x,y,QColor(pixel,pixel,pixel).rgba());

            pixel = 0;
        }
    return result;
}

QImage PIDTools::threshold(QImage image, int value)
{
    for(int x = 0; x < image.size().width(); x++)
        for(int y = 0; y < image.size().height(); y++)
            if(rgb(PIDTools::rgb2gray_scale(image.pixel(x,y))).r <= value)
                image.setPixel(x,y,0xff000000);
            else
                image.setPixel(x,y,0xffffffff);
    return image;
}

QImage PIDTools::RGB_Level(QImage image, qreal low, qreal high)
{
    // Lookup table pra acelerar o calculo
    int lookupTable[256];

    // Calculo da lookup table
    for(qreal i = 0; i < 256; i++)
    {
        int v = (int) ((i - low)*255.0/(high - low)); //Calcula o valor prum determinado nivel

        lookupTable[(int)i] = (v < 0 ? 0 :( v > 255 ? 255 : v)); // Saturador: garante um resultado entre 0 e 255
    }

    // Aplicacacao
    for(int x = 0; x < image.size().width(); x++)
        for(int y = 0; y < image.size().height(); y++)
            image.setPixel(x,y,QColor(
                               lookupTable[rgb(image.pixel(x,y)).r],
                               lookupTable[rgb(image.pixel(x,y)).g],
                               lookupTable[rgb(image.pixel(x,y)).b]
                               ).rgba());
    return image;
}

QImage PIDTools::brightnessContrast(QImage image, qreal brightness, qreal contrast)
{
    // Lookup table pra acelerar o calculo
    int lookupTable[256];

    // Calculo da lookup table
    for(qreal i = 0; i < 256; i++)
    {
        int v = (int) i*contrast + brightness; //Calcula o valor prum determinado nivel
        lookupTable[(int)i] = (v < 0 ? 0 :( v > 255 ? 255 : v)); // Saturador: garante um resultado entre 0 e 255
    }

    // Aplicacacao
    for(int x = 0; x < image.size().width(); x++)
        for(int y = 0; y < image.size().height(); y++)
            image.setPixel(x,y,QColor(
                               lookupTable[rgb(image.pixel(x,y)).r],
                               lookupTable[rgb(image.pixel(x,y)).g],
                               lookupTable[rgb(image.pixel(x,y)).b]
                               ).rgba());
    return image;
}
