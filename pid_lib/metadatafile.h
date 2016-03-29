#ifndef METADATAFILE_H
#define METADATAFILE_H

#include "pidtools.h"
#include "metadata.h"
#include <QString>

class MetadataFile
{

public:
    MetadataFile(QString path = "");

    bool read();

    void      setPath (QString path) { this->path = path; }
    QString getPath ()                    { return path;          }

    Metadata*                  getMetadata()        { return metadata;     }
    RGB_Data*                 getRGB()                { return rgb;               }
    HSV_Data*                 getHSV()                { return hsv;               }
    YUV_Data*                 getYUV()                { return yuv;               }
    Sampling_Data*          getSamplingData() { return samplingData; }

    static Metadata*         getMetadata       (QString path);
    static RGB_Data*        getRGB               (QString path);
    static HSV_Data*        getHSV                (QString path);
    static YUV_Data*        getYUV                (QString path);
    static Sampling_Data* getSamplingData (QString path);

private:
    RGB_Data* rgb;
    HSV_Data* hsv;
    YUV_Data* yuv;
    Sampling_Data* samplingData;
    Metadata* metadata;

    QString path;
};

#endif // METADATAFILE_H
