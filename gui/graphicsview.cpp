#include <QGraphicsItem>
#include "graphicsview.h"

GraphicsView::GraphicsView(QWidget* parent)
    :QGraphicsView(parent)
{
    abstractDraw = NULL;
    zoomValue = 1;
    modified = false;
    setScene(new QGraphicsScene());
    setBackgroundBrush(QBrush(QColor(100,100,100), Qt::Dense7Pattern));
    setMouseTracking(true);

}

void GraphicsView::setAbstractDraw(AbstractDraw* abstractDraw)
{
    this->abstractDraw = abstractDraw;
}

AbstractDraw* GraphicsView::getAbstractDraw()
{
    return abstractDraw;
}

void GraphicsView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::MidButton)
    {
        setDragMode(QGraphicsView::ScrollHandDrag);
        QGraphicsView::mousePressEvent(new QMouseEvent(
                                           event->type(),
                                           event->pos(),
                                           Qt::LeftButton,
                                           Qt::LeftButton,
                                           event->modifiers()));
    }
    else QGraphicsView::mousePressEvent(event);


    if(abstractDraw == NULL) return;
    abstractDraw->draw(event,this);
}

void GraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    QGraphicsView::mouseMoveEvent(event);

    QPointF ptF = mapToScene(event->pos());
    QPoint pt = ptF.toPoint();

    if(mouseTrackingLabel != NULL)
        mouseTrackingLabel->setText(QString("Mouse: %1, %2 px")
                                    .arg(pt.x())
                                    .arg(pt.y())
                                         );

    if(dragMode() == QGraphicsView::ScrollHandDrag)
        return;

    if(event->buttons() == Qt::LeftButton)
    {
        if(abstractDraw != NULL)
            abstractDraw->draw(event,this);
    }
}

void GraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    if(dragMode() == QGraphicsView::ScrollHandDrag) {
        setDragMode(QGraphicsView::NoDrag);
        QGraphicsView::mouseReleaseEvent(event);
        return;
    }
    else QGraphicsView::mouseReleaseEvent(event);



    if(abstractDraw == NULL) return;
    abstractDraw->draw(event,this);
    QImage* image = getQImage();
    clearScene();
    setQImage(image);
    modified = true;
    done();
}

QImage* GraphicsView::getQImage()
{
    scene()->clearSelection();
    QImage *image = new QImage(
                scene()->sceneRect().size().toSize(),
                QImage::Format_ARGB32);
    image->fill(Qt::transparent);
    QPainter painter(image);
    scene()->render(&painter);
    return image;
}

QImage* GraphicsView::getQImage(QGraphicsView* view)
{
    view->scene()->clearSelection();
    QImage *image = new QImage(
                view->scene()->sceneRect().size().toSize(),
                QImage::Format_ARGB32);
    image->fill(Qt::transparent);
    QPainter painter(image);
    view->scene()->render(&painter);
    return image;
}

void GraphicsView::setQImage(QImage* image)
{
   scene()->setSceneRect(QPixmap::fromImage(*image).rect());
   scene()->addPixmap(QPixmap::fromImage(*image));
}

void GraphicsView::clearScene()
{
    while (!scene()->items().isEmpty())
        delete scene()->items().takeFirst();
}

void GraphicsView::wheelEvent(QWheelEvent *event)
{
    if (event->delta() > 0) zoomIn(0.05);
    else zoomOut(0.05);
    event->accept();
}

void GraphicsView::zoomIn(qreal factor)
{
    zoomValue *= 1 + factor;
    QMatrix matrix;
    matrix.scale(zoomValue, zoomValue);
    setMatrix(matrix);
}

void GraphicsView::zoomOut(qreal factor)
{
    zoomValue *= 1 - factor;
    QMatrix matrix;
    matrix.scale(zoomValue, zoomValue);
    setMatrix(matrix);
}

void GraphicsView::normalSize()
{
    zoomValue = 1;
    QMatrix matrix;
    matrix.scale(zoomValue, zoomValue);
    setMatrix(matrix);
}


