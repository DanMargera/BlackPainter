#ifndef IMAGESLIDER_H
#define IMAGESLIDER_H

#include <QList>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QMouseEvent>

#define BORDER 20

class ImageSlider : public QGraphicsView
{
    Q_OBJECT

public:
    ImageSlider(QWidget * parent = 0);
    void appendImagePath(QString path);
    void prependImagePath(QString path);
    void insertImagePath(int i, QString path);
    void clear();

protected:
    void mouseDoubleClickEvent(QMouseEvent * event);

private:
    QList <QGraphicsPixmapItem*> *pixmapItemList;

signals:
    void imageDoubleClicked(QString path);

};

#endif // IMAGESLIDER_H
