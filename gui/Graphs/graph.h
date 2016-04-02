#ifndef GRAPH_H
#define GRAPH_H

#include <QWidget>
#include <QVector>
#include <QMouseEvent>

class Graph : public QWidget
{
    Q_OBJECT

public:

    Graph(QWidget * parent = 0);

    void setData(QVector<QPointF> data);
    QVector<QPointF> getData()          { return data;       }
 
protected:
    void paintEvent(QPaintEvent * event);
    void mouseDoubleClickEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent * event);

private:
    QVector<QPointF> data;
    qreal intersect(QPolygonF p, qreal x);
    QPolygonF translate(QPolygonF polygon);
    qreal x;

signals:
	void mouseDoubleClick();
};

#endif // GRAPH_H
