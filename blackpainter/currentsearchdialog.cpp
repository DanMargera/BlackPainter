#include "currentsearchdialog.h"

CurrentSearchDialog::CurrentSearchDialog(QWidget * parent)
    : QDialog(parent)
{
    setMaximumSize(QSize(220,130));
    setMinimumSize(QSize(220,130));
    setWindowTitle(tr("Similar Images"));

    createWidgets();
    createLayout();
}

void CurrentSearchDialog::createWidgets()
{
    comparisonLabel     = new QLabel    (tr("Histogram:"),this);
    comparisonBox = new QComboBox;
    comparisonBox->addItem(tr("RGB"));
    comparisonBox->addItem(tr("HSV"));
    comparisonBox->addItem(tr("YUV"));
    comparisonBox->addItem(tr("Sampling"));


    distanceLabel     = new QLabel    (tr("Distance Method:"),this);
    distanceBox = new QComboBox;
    distanceBox->addItem(tr("Manhattan"));
    distanceBox->addItem(tr("Euclidean"));
    distanceBox->addItem(tr("Chess"));
    distanceBox->addItem(tr("Cosine"));

    searchBtn       = new QPushButton (tr("Search"),this);
    cancelBtn       = new QPushButton (tr("Cancel"),this);

    connect(cancelBtn,SIGNAL(clicked(bool)),this,SLOT(close()));
    connect(searchBtn,SIGNAL(clicked(bool)),this,SLOT(accept()));
}

void CurrentSearchDialog::createLayout()
{
    QGridLayout* layout = new QGridLayout();

    layout->addWidget(comparisonLabel,1,0,1,2, Qt::AlignRight);
    layout->addWidget(comparisonBox,1,2,1,2, Qt::AlignLeft);

    layout->addWidget(distanceLabel,2,0,1,2, Qt::AlignRight);
    layout->addWidget(distanceBox,2,2,1,2, Qt::AlignLeft);

    layout->addWidget(cancelBtn,3,0,1,2, Qt::AlignBottom | Qt::AlignLeft);
    layout->addWidget(searchBtn,3,2,1,2, Qt::AlignBottom | Qt::AlignRight);

    setLayout(layout);
}

int CurrentSearchDialog::selectedComparisonType()
{
    int index = comparisonBox->currentIndex();
    switch (index) {
    case 0:
        return Rgb;
    case 1:
        return Hsv;
    case 2:
        return Yuv;
    case 3:
        return Sampling;
    default:
        return 0;
    }
}

int CurrentSearchDialog::selectedDistanceMethod()
{
    int index = distanceBox->currentIndex();
    switch (index) {
    case 0:
        return Manhattan;
    case 1:
        return Euclidean;
    case 2:
        return Chess;
    case 3:
        return Cosine;
    default:
        return 0;
    }
}

