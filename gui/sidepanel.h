#ifndef SIDEPANEL_H
#define SIDEPANEL_H

#include <QGraphicsView>
#include <QToolBox>
#include <QLabel>
#include <Graphs/histogram.h>
#include <Graphs/graph.h>

class SidePanel : public QToolBox
{
    Q_OBJECT

public:
    SidePanel(QWidget * parent = 0, Qt::WindowFlags f = 0);
    void setScene(QGraphicsScene* scene);
    QGraphicsView* getGraphicsView() { return graphicsView; }
    Histogram* getHistogram()        { return histogram;    }
    void setGraphData(QVector <QPointF> data);

private:
    QGraphicsView* graphicsView;
    Histogram* histogram;
    QWidget* propertiesWidget;
    Graph* graph;


    QWidget* createInfo       ();
    QWidget* createAnalysis   ();
    QWidget* createRecallGraph();
};

#endif // SIDEPANEL_H
