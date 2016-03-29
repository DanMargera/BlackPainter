#ifndef GRAPHV2_H
#define GRAPHV2_H

#include <QGraphicsView>

class GraphV2 : QGraphicsView
{
    Q_OBJECT

public:
    GraphV2(QWidget * parent = 0);

    void setData(QVector<QPointF> data) { this->data = data; draw(); }

private:
    QVector<QPointF> data;
    void draw();
};

#endif // GRAPHV2_H
