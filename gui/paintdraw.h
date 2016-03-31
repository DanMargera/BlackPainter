#ifndef PAINTDRAW_H
#define PAINTDRAW_H

#include "abstractdraw.h"

class PaintDraw : public AbstractDraw
{
public:
    PaintDraw(QColor fillColor = QColor(0,0,0));

    void draw(QMouseEvent *event, QGraphicsView* view);
};

#endif // PAINTDRAW_H
