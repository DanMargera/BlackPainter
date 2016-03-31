#include "imageslider.h"

#include <QDebug>
#include <QPixmap>
#include <QVariant>

ImageSlider::ImageSlider(QWidget * parent)
    : QGraphicsView(parent)
{
    setScene(new QGraphicsScene());
    setBackgroundBrush(QBrush(QColor(100,100,100), Qt::SolidPattern));

    setMinimumHeight(150);
    setMinimumHeight(150);

    pixmapItemList = new QList<QGraphicsPixmapItem*>();
}

void ImageSlider::appendImagePath(QString path)
{
    QPixmap pixmap(path);
    pixmap = pixmap.scaledToHeight(100);
    QGraphicsPixmapItem* pixmapItem = scene()->addPixmap(pixmap);
    pixmapItem->setData(0,QVariant(path));

    if(pixmapItemList->length() > 0)
        pixmapItem->setOffset(QPointF(
            pixmapItemList->last()->offset().x()
            +pixmapItemList->last()->boundingRect().width()
            +BORDER
            ,0));

    pixmapItemList->append(pixmapItem);
}

void ImageSlider::prependImagePath(QString path)
{
    QPixmap pixmap(path);
    pixmap = pixmap.scaledToHeight(100);
    QGraphicsPixmapItem* pixmapItem = scene()->addPixmap(pixmap);
    pixmapItem->setData(0,QVariant(path));

    if(pixmapItemList->length() > 0)
        pixmapItem->setOffset(QPointF(
            pixmapItemList->first()->offset().x()
            -pixmap.width()
            -BORDER
            ,0));

    pixmapItemList->prepend(pixmapItem);
}

void ImageSlider::insertImagePath(int i, QString path)
{
    //Implementar
}

void ImageSlider::clear()
{
    setScene(new QGraphicsScene());
    pixmapItemList->clear();
}

void ImageSlider::mouseDoubleClickEvent(QMouseEvent * event)
{
    QList<QGraphicsItem*> itemsList = scene()->items(mapToScene(event->pos()));

    if(itemsList.length() > 1) qDebug() << "Algo deu errado";

    if(itemsList.length())
    {
        qDebug() << itemsList.first()->data(0).toString();
        imageDoubleClicked(itemsList.first()->data(0).toString());
    }
}
