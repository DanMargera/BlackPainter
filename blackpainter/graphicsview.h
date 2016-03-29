#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include "abstractdraw.h"
#include <QGraphicsView>
#include <QImage>
#include <QLabel>



class GraphicsView : public QGraphicsView
{
    Q_OBJECT

public:
    GraphicsView(QWidget * parent = 0);

    void setAbstractDraw(AbstractDraw* abstractDraw);
    AbstractDraw* getAbstractDraw();
    QImage* getQImage();
    static QImage* getQImage(QGraphicsView* view);
    void setQImage(QImage* image);
    void clearScene();


    bool isModified() { return modified; }
    void setModifed(bool modified) { this->modified = modified; }
    void setMouseTrackingLabel(QLabel* label) { mouseTrackingLabel = label; }

public slots:
    void zoomIn(qreal factor);
    void zoomOut(qreal factor);
    void normalSize();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

signals:
    void done();
    void mousePos(QPoint point);

private:
    AbstractDraw* abstractDraw;
    qreal zoomValue;
    bool modified;

    QLabel* mouseTrackingLabel;

};

#endif // GRAPHICSVIEW_H
