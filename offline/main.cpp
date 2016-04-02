
#include <QFileInfo>
#include <QDirIterator>
#include <QTextStream>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>
#include <QDebug>
#include <QImage>
#include <pidtools.h>
#include <multi_vector.h>
#include <QString>

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

         /*
         * Tenta criar e abrir um arquivo de texto em modo de escrita
         * com o nome de (Imagem.jpg).data
         */
        QFile file(next.append(".data"));
        if(file.exists())
        {
            file.close();
            continue;
        }

        /*
         * Extrai os dados da imagem
         */
        QImage image(next);
        RGB_Data* rgbData = PIDTools::rgbHistogram(image);
        HSV_Data* hsvData = PIDTools::hsvHistogram(image);
        YUV_Data* yuvData = PIDTools::yuvHistogram(image);


        QJsonObject jsonObject;

        QJsonObject jsonObjectRGB;
        QJsonArray jsonArrayRGB_r;
        QJsonArray jsonArrayRGB_g;
        QJsonArray jsonArrayRGB_b;

        QJsonObject jsonObjectHSV;
        QJsonArray jsonArrayHSV_h;
        QJsonArray jsonArrayHSV_s;
        QJsonArray jsonArrayHSV_v;

        QJsonObject jsonObjectYUV;
        QJsonArray jsonArrayYUV_y;
        QJsonArray jsonArrayYUV_u;
        QJsonArray jsonArrayYUV_v;

        for(int i = 0; i < rgbData->r->size(); i++)
        {

            jsonArrayRGB_r.append(QJsonValue(rgbData->r->at(i)));
            jsonArrayRGB_g.append(QJsonValue(rgbData->g->at(i)));
            jsonArrayRGB_b.append(QJsonValue(rgbData->b->at(i)));

        }
        for(int i = 0; i < hsvData->h->size(); i++)
        {
            jsonArrayHSV_h.append(QJsonValue(hsvData->h->at(i)));
            jsonArrayHSV_s.append(QJsonValue(hsvData->s->at(i)));
            jsonArrayHSV_v.append(QJsonValue(hsvData->v->at(i)));
        }

        for(int i = 0; i < yuvData->y->size(); i++)
        {
            jsonArrayYUV_y.append(QJsonValue(yuvData->y->at(i)));
            jsonArrayYUV_u.append(QJsonValue(yuvData->u->at(i)));
            jsonArrayYUV_v.append(QJsonValue(yuvData->v->at(i)));
        }

        jsonObjectRGB.insert(QString("R"),jsonArrayRGB_r);
        jsonObjectRGB.insert(QString("G"),jsonArrayRGB_g);
        jsonObjectRGB.insert(QString("B"),jsonArrayRGB_b);

        jsonObjectHSV.insert(QString("H"),jsonArrayHSV_h);
        jsonObjectHSV.insert(QString("S"),jsonArrayHSV_s);
        jsonObjectHSV.insert(QString("V"),jsonArrayHSV_v);

        jsonObjectYUV.insert(QString("Y"),jsonArrayYUV_y);
        jsonObjectYUV.insert(QString("U"),jsonArrayYUV_u);
        jsonObjectYUV.insert(QString("V"),jsonArrayYUV_v);

        jsonObject.insert(QString("RGB"),jsonObjectRGB);
        jsonObject.insert(QString("HSV"),jsonObjectHSV);
        jsonObject.insert(QString("YUV"),jsonObjectYUV);

        QJsonDocument json(jsonObject);



        if (!file.open(QFile::WriteOnly | QFile::Text)) {
            qDebug() << "Erro ao criar base de dados";
            return 2;
        }
        QTextStream out(&file);
        out << json.toJson();
        file.close();

    }

    return 0;
}
