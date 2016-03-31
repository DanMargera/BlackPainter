#ifndef SIDEPANEL_H
#define SIDEPANEL_H

#include <QGraphicsView>
#include <QToolBox>
#include <QLabel>
#include <histogram.h>
#include <graph.h>

class SidePanel : public QToolBox
{
    Q_OBJECT

public:
    SidePanel(QWidget * parent = 0, Qt::WindowFlags f = 0);
    void setScene(QGraphicsScene* scene);
    QGraphicsView* getGraphicsView() { return graphicsView; }
    Histogram* getHistogram()        { return histogram;    }

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
