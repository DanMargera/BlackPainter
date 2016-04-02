#include <QFileInfo>
#include <QDirIterator>
#include <QTextStream>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>
#include <QDebug>
#include <QImage>
#include <QDataStream>
#include <QFile>
#include <pidtools.h>
#include <multi_vector.h>
#include <QString>



QVector<quint8>* get8bit(QVector<int> *vec) {
    QVector<quint8>* v8 = new QVector<quint8>(vec->size(),0);
    quint8 bint;
    for (int i=0;i<v8->size();i++) {
        bint = (unsigned char)((*vec)[i]);
        (*v8)[i] = bint;
    }
    return v8;
}

int main(int argc, char *argv[])
{
    MultiVector<int,10> mult({"R","G","B"});
    (*mult["R"])[0] = 1;

    qDebug() << "PROGRAMA CHAMADO: "<< endl
                    << argv[0] << endl;

    QString path; //Caminho da pasta

    /*
     * Caso nenhum parametro seja passado, utiliza o caminho
     * da pasta do executavel
     */
    if(argc == 1) //Nenhum parametro passado
    {
        QString programPath(argv[0]);
        QFileInfo fileInfo(programPath);
        path = fileInfo.absolutePath();
    }

    /*
     * Caso mais de um argumento seja passado, termina o
     * programa retornando 1
     */
    else if(argc > 2)
    {
        return 1;
    }

    /*
     * Caso o numero correto de parametros sejam passados,
     * continua a execucao
     */
    else
    {
        path = QString(argv[1]);
    }

    /*
     * Cria um iterator com os arquivos *.jpg presentes na
     * pasta do caminho path
     */
    QDirIterator it(path, QStringList() << "*.jpg", QDir::Files, QDirIterator::NoIteratorFlags);

    /*
     * Acessa cada imagem individualmente
     */
    while (it.hasNext())
    {
        /*
         * Obtem endereco de cada imagem individualmente
         */
        QString next = it.next();
        QImage image(next);

         /*
         * Tenta criar e abrir um arquivo de texto em modo de escrita
         * com o nome de (Imagem.jpg).data
         */
        QFile file(next.append(".data"));
        if(file.exists() || !file.open(QIODevice::WriteOnly))
        {
            file.close();
            continue;
        }

        /*
         * Extrai os dados da imagem
         */
        RGB_Data* rgbData = PIDTools::rgbData(image);
        HSV_Data* hsvData = PIDTools::hsvData(image);
        YUV_Data* yuvData = PIDTools::yuvData(image);

        // RGB
        QVector<quint8>* rData = get8bit(rgbData->r);
        QVector<quint8>* gData = get8bit(rgbData->g);
        QVector<quint8>* bData = get8bit(rgbData->b);

        // HSV
        QVector<quint8>* hData = get8bit(hsvData->h);
        QVector<quint8>* sData = get8bit(hsvData->s);
        QVector<quint8>* vData = get8bit(hsvData->v);

        // YUV
        QVector<quint8>* yData = get8bit(yuvData->y);
        QVector<quint8>* uData = get8bit(yuvData->u);
        QVector<quint8>* valData = get8bit(yuvData->v);

        QDataStream ds(&file);
        ds.setVersion(QDataStream::Qt_5_5);

        for (int i=0;i<rData->size();i++) {
            ds << (*rData)[i];
            ds << (*gData)[i];
            ds << (*bData)[i];
            ds << (*hData)[i];
            ds << (*sData)[i];
            ds << (*vData)[i];
            ds << (*yData)[i];
            ds << (*uData)[i];
            ds << (*valData)[i];
        }

        file.close();
    }

    return 0;
}
