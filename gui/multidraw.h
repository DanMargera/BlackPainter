#ifndef MULTIDRAW_H
#define MULTIDRAW_H

#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>

#include "abstractdraw.h"

class RectDraw : public AbstractDraw
{
public:
    RectDraw(QColor borderColor = QColor(0,0,0),
             QColor fillColor = QColor(255,255,255),
             int borderWidth = 1);

    void draw(QMouseEvent *event, QGraphicsView* view);
private:
    QGraphicsRectItem* rect;
};

class EllipseDraw : public AbstractDraw
{
public:
    EllipseDraw(QColor borderColor = QColor(0,0,0),
             QColor fillColor = QColor(255,255,255),
                int borderWidth = 1);

    void draw(QMouseEvent *event, QGraphicsView* view);
private:
    QGraphicsEllipseItem* ellipse;
};

class LineDraw : public AbstractDraw
{
public:
    LineDraw(QColor borderColor = QColor(0,0,0),
             int borderWidth = 1);

    void draw(QMouseEvent *event, QGraphicsView* view);
private:
    QGraphicsLineItem* line;
};

class PencilDraw : public AbstractDraw
{
public:
    PencilDraw(QColor borderColor = QColor(0,0,0),
               int borderWidth = 1);

    void draw(QMouseEvent *event, QGraphicsView* view);
private:
    QGraphicsLineItem* line;
};

#endif // MULTIDRAW_H
