#include "multidraw.h"
#include <QDebug>
#include <QEvent>
#include <QPen>
#include <QBrush>
#include <QtMath>


#define ABS(v1)           ((v1) > 0)?(v1):-(v1)
#define MAX(v1,v2)        ((v1) > (v2))?(v1):(v2)
#define MIN(v1,v2)        ((v1) < (v2))?(v1):(v2)
#define HIP(x1,y1)        qSqrt((x1)*(x1)+(y1)*(y1))
#define HIP2(x1)          qSqrt(2)*(x1)
#define HIP3(x1,x2,y1,y2) qSqrt( ((x1)-(x2))*((x1)-(x2))+((y1)-(y2))*((y1)-(y2)) )


QPointF pt1;

RectDraw::RectDraw(QColor borderColor, QColor fillColor, int borderWidth)
{
    setBorderColor(borderColor);
    setBorderWidth(borderWidth);
    setFillColor(fillColor);
}

void RectDraw::draw(QMouseEvent *event, QGraphicsView* view)
{
    if(event->type() == QEvent::MouseButtonPress)
    {
        QPen pen(borderColor);
        pen.setWidth(borderWidth);


        pt1 = view->mapToScene(event->pos());
        rect = new QGraphicsRectItem();
        rect->setPen(pen);
        rect->setBrush(QBrush(fillColor));
        view->scene()->addItem(rect);
        toolTracking(QString("Pencil - POS: %1, %2 px SIZE: 0, 0 px").arg(pt1.x()).arg(pt1.y()));
    }
    else if(event->type() == QEvent::MouseMove)
    {
        QPointF pt2 = view->mapToScene(event->pos());
        qreal width = pt2.x()-pt1.x();
        qreal height = pt2.y()-pt1.y();
        rect->setRect(MIN(pt2.x(),pt1.x()),
                      MIN(pt2.y(),pt1.y()),
                      ABS(width), ABS(height));

        toolTracking(QString("Pencil - POS: %1, %2 px SIZE: %3, %4 px")
                     .arg(MIN(pt2.x(),pt1.x()))
                     .arg(MIN(pt2.y(),pt1.y()))
                     .arg(ABS(width))
                     .arg(ABS(height))
                     );
    }
}

EllipseDraw::EllipseDraw(QColor borderColor, QColor fillColor, int borderWidth)
{
    setBorderColor(borderColor);
    setBorderWidth(borderWidth);
    setFillColor(fillColor);
}

void EllipseDraw::draw(QMouseEvent *event, QGraphicsView* view)
{
    if(event->type() == QEvent::MouseButtonPress)
    {
        QPen pen(borderColor);
        pen.setWidth(borderWidth); //TEMP


        pt1 = view->mapToScene(event->pos());
        ellipse = new QGraphicsEllipseItem();
        ellipse->setPen(pen);
        ellipse->setBrush(QBrush(fillColor));
        view->scene()->addItem(ellipse);
        toolTracking(QString("Pencil - POS: %1, %2 px SIZE: 0, 0 px").arg(pt1.x()).arg(pt1.y()));

    }
    else if(event->type() == QEvent::MouseMove)
    {
        QPointF pt2 = view->mapToScene(event->pos());
        qreal width = pt2.x()-pt1.x();
        qreal height = pt2.y()-pt1.y();
        ellipse->setRect(MIN(pt2.x(),pt1.x()),
                      MIN(pt2.y(),pt1.y()),
                      ABS(width), ABS(height));

        toolTracking(QString("Pencil - POS: %1, %2 px SIZE: %3, %4 px")
                     .arg(MIN(pt2.x(),pt1.x()))
                     .arg(MIN(pt2.y(),pt1.y()))
                     .arg(ABS(width))
                     .arg(ABS(height))
                     );
    }
}

LineDraw::LineDraw(QColor borderColor, int borderWidth)
{
    setBorderColor(borderColor);
    setBorderWidth(borderWidth);
}

void LineDraw::draw(QMouseEvent *event, QGraphicsView* view)
{
    if(event->type() == QEvent::MouseButtonPress)
    {
        QPen pen(borderColor);
        pen.setWidth(borderWidth);
        pen.setJoinStyle(Qt::RoundJoin);
        pen.setCapStyle(Qt::RoundCap);

        pt1 = view->mapToScene(event->pos());

        line = new QGraphicsLineItem();
        line->setPen(pen);
        view->scene()->addItem(line);

        toolTracking(QString("Line - P1: %1, %2 px P2: %1 , %2 px D: 0 px")
                     .arg(pt1.x())
                     .arg(pt1.y()));
    }
    else if(event->type() == QEvent::MouseMove)
    {
        QPointF pt2 = view->mapToScene(event->pos());


        line->setLine(pt1.x(),
                      pt1.y(),
                      pt2.x(),
                      pt2.y());

        toolTracking(QString("Line - P1: %1, %2 px P2: %3 , %4 px D: %5 px")
                     .arg(pt1.x())
                     .arg(pt1.y())
                     .arg(pt2.x())
                     .arg(pt2.y())
                     .arg(HIP3(pt1.x(),pt1.y(),pt2.x(),pt2.y())));
    }
}

PencilDraw::PencilDraw(QColor borderColor, int borderWidth)
{
    setBorderColor(borderColor);
    setBorderWidth(borderWidth);
}

void PencilDraw::draw(QMouseEvent *event, QGraphicsView* view)
{
    QPen pen(borderColor);
    pen.setWidth(borderWidth);
    pen.setJoinStyle(Qt::RoundJoin);
    pen.setCapStyle(Qt::RoundCap);

    if(event->type() == QEvent::MouseButtonPress)
    {
        pt1 = view->mapToScene(event->pos());
        toolTracking(QString("Pencil - position: %1, %2 px").arg(pt1.x()).arg(pt1.y()));
    }
    else if(event->type() == QEvent::MouseMove)
    {
        QPointF pt2 = view->mapToScene(event->pos());
        toolTracking(QString("Pencil - position: %1, %2 px").arg(pt2.x()).arg(pt2.y()));
        view->scene()->addLine(pt1.x(),
                               pt1.y(),
                               pt2.x(),
                               pt2.y(),
                               pen);
        pt1 = pt2;
    }
}


