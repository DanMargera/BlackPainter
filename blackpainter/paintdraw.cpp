#include "paintdraw.h"
#include <QStack>
#include <QDebug>
#include "graphicsview.h"

PaintDraw::PaintDraw(QColor fillColor)
{
    setFillColor(fillColor);
}

bool isValid (QRect rect, int x, int y)
{
    if(x < 0 ||
            y < 0 ||
            x >= rect.width() ||
            y >= rect.height()) return false;
    else return true;
}

void PaintDraw::draw(QMouseEvent *event, QGraphicsView* view)
{
    if(event->type() != QEvent::MouseButtonPress) return;
    QPointF ptF = view->mapToScene(event->pos());
    QPoint pt = ptF.toPoint();


    QImage* image = GraphicsView::getQImage(view);
    QRect rect = image->rect();
    QStack <QPoint> *pointStack = new QStack<QPoint>();

    if(isValid( rect , pt.x() , pt.y() ) &&
            image->pixel(pt.x(),pt.y()) != getFillColor().rgb())
        pointStack->push(pt);
    else return;

    toolTracking(QString("Paint Bucket - position: %1, %2 px").arg(pt.x()).arg(pt.y()));

    QRgb seed = image->pixel(pt.x(),pt.y());
    while(!pointStack->isEmpty())
    {
        pt = pointStack->pop();
        image->setPixel(pt.x(),pt.y(),getFillColor().rgb());

        if( isValid( rect , pt.x()-1 , pt.y() ) &&
                image->pixel( pt.x()-1 , pt.y() ) == seed )
            pointStack->push(QPoint( pt.x()-1 , pt.y() ));

        if( isValid( rect , pt.x()+1 , pt.y() ) &&
                image->pixel( pt.x()+1 , pt.y() ) == seed )
            pointStack->push(QPoint( pt.x()+1 , pt.y() ));

        if( isValid( rect , pt.x() , pt.y()-1 ) &&
                image->pixel( pt.x() , pt.y()-1 ) == seed )
            pointStack->push(QPoint( pt.x() , pt.y()-1 ));

        if( isValid( rect , pt.x() , pt.y()+1 ) &&
                image->pixel( pt.x() , pt.y()+1 ) == seed )
            pointStack->push(QPoint( pt.x() , pt.y()+1 ));
    }

   delete pointStack;

    view->scene()->setSceneRect(QPixmap::fromImage(*image).rect());
    view->scene()->addPixmap(QPixmap::fromImage(*image));
}


