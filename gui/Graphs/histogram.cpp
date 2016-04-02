#include <QPainter>
#include <QtCore/qmath.h>
#include "histogram.h"
#include <QPointF>
#include <QPolygonF>
#include <QDebug>

Histogram::Histogram(QWidget * parent)
    : QWidget(parent)
{
    vector = NULL;
}

void Histogram::paintEvent(QPaintEvent * event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);


    painter.setBrush(QColor(249,249,249));
    painter.setPen(QPen(QColor(162,162,162), 1, Qt::SolidLine,
                        Qt::FlatCap, Qt::MiterJoin));
    painter.drawRect(0,0,geometry().width()-1,geometry().height()-1);

    painter.setPen(QPen(QColor(0,0,0), 0.5, Qt::SolidLine,
                        Qt::FlatCap, Qt::MiterJoin));

    if(vector == NULL) return;

    QPainterPath redPath;
    QPainterPath greenPath;
    QPainterPath bluePath;

    QPolygonF redPoligon;
    QPolygonF greenPoligon;
    QPolygonF bluePoligon;

    redPoligon   << translate(0,0);
    greenPoligon << translate(0,0);
    bluePoligon  << translate(0,0);

    for (int i = 0; i < 256; i++)
    {
        redPoligon   << translate(i,(*vector->r)[i]);
        greenPoligon << translate(i,(*vector->g)[i]);
        bluePoligon  << translate(i,(*vector->b)[i]);
    }

    redPoligon   << translate(255,0);
    greenPoligon << translate(255,0);
    bluePoligon  << translate(255,0);


    bluePath.addPolygon(bluePoligon);
    greenPath.addPolygon(greenPoligon);
    redPath.addPolygon(redPoligon);

    painter.setBrush(QColor(0,0,255,150));
    painter.drawPath(bluePath);
    painter.setBrush(QColor(0,255,0,150));
    painter.drawPath(greenPath);
    painter.setBrush(QColor(255,0,0,150));
    painter.drawPath(redPath);
}

QPointF Histogram::translate(qreal x, qreal y)
{
    QRectF rect = geometry();
    x = x/vector->xMax*(rect.width()-6) + 2;
    y = rect.height() - y/vector->yMax*rect.height();
    return QPointF(x,y);
}

void Histogram::setRGBHistogram(RGB_Data* vector)
{
    this->vector = vector;
    repaint();
}

void Histogram::mouseDoubleClickEvent(QMouseEvent * event)
{
    Q_UNUSED(event)
    mouseDoubleClick();
}
