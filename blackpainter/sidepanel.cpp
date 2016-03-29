#include "sidepanel.h"
#include <QLabel>
#include <QPushButton>
#include <QSizePolicy>
#include <QToolBox>
#include <QGridLayout>
#include <QLayout>

SidePanel::SidePanel(QWidget * parent, Qt::WindowFlags f)
    : QToolBox(parent,f)
{

    setMaximumWidth(230);
    setMinimumWidth(230);

   addItem(createInfo(),    tr("Info"));
   addItem(createAnalysis(),tr("Analysis"));
   addItem(createRecallGraph(),  tr("Results"));


}

void SidePanel::setScene(QGraphicsScene* scene)
{
    graphicsView->setScene(scene);
    graphicsView->fitInView(graphicsView->scene()->sceneRect(),Qt::KeepAspectRatio);
}


QWidget* SidePanel::createInfo()
{
    QWidget* basicInfoWidget = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout();
    basicInfoWidget->setLayout(layout);

    layout->addWidget(new QLabel(tr("Preview")),0,Qt::AlignHCenter);

    graphicsView = new QGraphicsView(this);
    graphicsView->setMaximumHeight(150);
    graphicsView->setMinimumHeight(150);
    graphicsView->setMinimumWidth(200);
    layout->addWidget(graphicsView);


    layout->addWidget(new QLabel(tr("File properties")),0,Qt::AlignHCenter);
    propertiesWidget = new QWidget(this);
    QGridLayout* gridLayout = new QGridLayout(this);
    propertiesWidget->setLayout(gridLayout);

    QLabel* nameLabel   = new QLabel("Name:",this);
    QLabel* folderLabel = new QLabel("Folder:",this);
    QLabel* sizeLabel   = new QLabel("Size:",this);

    gridLayout->addWidget(nameLabel,0,0);
    gridLayout->addWidget(folderLabel,1,0);
    gridLayout->addWidget(sizeLabel,2,0);

    layout->addWidget(propertiesWidget);
    layout->addSpacerItem(new QSpacerItem(1,1,QSizePolicy::Minimum,QSizePolicy::Expanding));

    return basicInfoWidget;
}

QWidget* SidePanel::createAnalysis()
{
    QWidget* analysisWidget = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout();
    analysisWidget->setLayout(layout);

    layout->addWidget(new QLabel(tr("Histogram")),0,Qt::AlignHCenter);

    histogram = new Histogram(this);
    histogram->setMaximumHeight(150);
    histogram->setMinimumHeight(150);
    histogram->setMinimumWidth(200);
    layout->addWidget(histogram);

    layout->addSpacerItem(new QSpacerItem(1,1,QSizePolicy::Minimum,QSizePolicy::Expanding));

    return analysisWidget;
}

QWidget* SidePanel::createRecallGraph()
{


    QWidget* recallWidget = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout();
    recallWidget->setLayout(layout);

    layout->addWidget(new QLabel(tr("Precision x Recall")),0,Qt::AlignHCenter);

    graph = new Graph(this);
    graph->setMaximumHeight(150);
    graph->setMinimumHeight(150);
    graph->setMinimumWidth(200);
    layout->addWidget(graph);


    QVector<QPointF> data;
    data << QPointF(0,50)
         << QPointF(10,100)
         << QPointF(20,67)
         << QPointF(30,50)
         << QPointF(40,40)
         << QPointF(50,33)
         << QPointF(60,0)
         << QPointF(70,0)
         << QPointF(80,0)
         << QPointF(90,0)
         << QPointF(100,100);

    graph->setData(data);



    layout->addSpacerItem(new QSpacerItem(1,1,QSizePolicy::Minimum,QSizePolicy::Expanding));

    return recallWidget;
}


