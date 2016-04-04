#include "graph.h"
#include <QPainter>
#include <QPainterPath>
#include <QDebug>

Graph::Graph(QWidget * parent)
    : QWidget(parent)
{
    setMouseTracking(true);
}

void Graph::paintEvent(QPaintEvent * event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    qreal rHeight = height();
    qreal rWidth = width();



    // Desenho o fundo
    painter.setBrush(QColor(249,249,249));
    painter.setPen(QPen(QColor(162,162,162), 1, Qt::SolidLine,
                        Qt::FlatCap, Qt::MiterJoin));
    painter.drawRect(0,0,geometry().width()-1,geometry().height()-1);


    QTransform transform;
    transform.translate(rWidth*20.0/240.0,rHeight*20.0/240.0);
    transform.scale(100.0/120.0, 100.0/120.0);


    painter.setTransform(transform);

    QPolygonF graph(data);
    graph = translate(graph);
    QPainterPath path;
    path.addPolygon(graph);



    // Da um jeito nas coordenadas
//    painter.translate(0,height());
//    painter.scale(1,-1);

    painter.setPen(QPen(QBrush(QColor(22,22,22)),0.5,Qt::SolidLine,Qt::RoundCap));
    for(qreal i = 0; i <= rHeight; i += rHeight/10.0)
        painter.drawLine(QLineF(-rWidth*0.1,i,rWidth*1.1,i));

    painter.setPen(QPen(QBrush(QColor(22,22,22)),0.5,Qt::DashLine,Qt::RoundCap));
    for(qreal i = 0; i <= rWidth; i += rWidth/10.0)
        painter.drawLine(QLineF(i,-rHeight*0.1,i,rHeight*1.1));

    painter.setBrush(QBrush(QColor(0,0,0,0)));
    painter.setPen(QPen(QBrush(QColor(0,0,0)),1,Qt::SolidLine,Qt::RoundCap));
    painter.drawRect(0,0,width(),height());

    painter.drawLine(QLineF(-rWidth*0.1,0,rWidth*1.1,0));
    painter.drawLine(QLineF(0,-rHeight*0.1,0,rHeight*1.1));

    painter.setRenderHint(QPainter::Antialiasing);

    painter.setPen(QColor(0,0,255));
    painter.drawPolyline(graph);

    qreal bolinha = 9;

    painter.setBrush(QBrush(QColor(0,0,0,0)));
    painter.setPen(QPen(QBrush(QColor(255,0,0)),0.5,Qt::SolidLine,Qt::SquareCap));


    qreal xs = (x < rWidth/12.0 ? rWidth/12.0 : x > rWidth*11.0/12.0 ? rWidth*11.0/12.0 : x);

    xs = (xs- rWidth/12.0)*12/10 ;

    qreal yVal = intersect(graph,xs);
    painter.drawRect(xs-bolinha/2.0, yVal-bolinha/2.0,bolinha,bolinha);
    painter.drawLine(QLineF(0,yVal,rWidth,yVal));
    painter.drawText(rWidth+3, yVal, QString::number((int)(((rHeight-yVal)/rHeight)*100)));

    painter.resetTransform();
    painter.setRenderHint(QPainter::Antialiasing,false);
    painter.setPen(QColor(0,0,0));

    qreal xLim = x > rWidth*11/12 ? rWidth*11/12 : x < rWidth*1/12 ? rWidth*1/12 : x;
    painter.drawLine(QLineF(xLim,0,xLim,height()));
}


QPolygonF Graph::translate(QPolygonF p)
{
    for(int i = 0; i < p.size(); i++)
    {
        p[i] = QPointF(
                    p[i].x()*((qreal)width())/100.0
                    ,
                    p[i].y()*((qreal)height())/100.0
                    );
    }
    return p;
}



void Graph::mouseDoubleClickEvent(QMouseEvent * event)
{
    Q_UNUSED(event)
    mouseDoubleClick();
}

void Graph::mouseMoveEvent(QMouseEvent * event)
{
    x = event->x();
    repaint();
}

qreal Graph::intersect(QPolygonF p, qreal x)
{
    for(int i = 1; i < p.size(); i++)
    {
        if(x > p.at(i-1).x() && x <= p.at(i).x())
        {
            QLineF line(p.at(i-1),p.at(i));
            qreal alpha = line.dy()/line.dx();
            qreal delta = line.p1().y() - alpha*line.p1().x();
            return x*alpha+delta;
        }
    }
    if(x < p.first().x())
        return p.first().y();
    else
        return p.last().y();
}

void Graph::setData(QVector<QPointF> d) {
    this->data = d;
    for (int i=0;i<data.length();i++) {
        data[i].setY(100-data[i].y());
    }
}
