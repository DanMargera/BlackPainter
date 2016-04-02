#include "currentsearchdialog.h"
#include <QtMath>

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
    comparisonLabel     = new QLabel(tr("Histogram:"),this);
    comparisonBox = new QComboBox;
    comparisonBox->addItem(tr("RGB"));
    comparisonBox->addItem(tr("HSV"));
    comparisonBox->addItem(tr("YUV"));


    distanceLabel     = new QLabel(tr("Distance Method:"),this);
    distanceBox = new QComboBox;
    distanceBox->addItem(tr("Manhattan"));
    distanceBox->addItem(tr("Euclidean"));
    distanceBox->addItem(tr("Chess"));
    distanceBox->addItem(tr("Cosine"));

    samplingLabel = new QLabel(tr("Sampling:"));
    valueLineEdit    = new QLineEdit(QString::number(8),this);
    valueLineEdit->setValidator(new QIntValidator(8,64,this));
    valueLineEdit->setReadOnly(true);
    samplingSlider = new QSlider(this);
    samplingSlider->setValue(3);
    samplingSlider->setMinimum(3);
    samplingSlider->setMaximum(6);
    samplingSlider->setOrientation(Qt::Horizontal);

    searchBtn       = new QPushButton (tr("Search"),this);
    cancelBtn       = new QPushButton (tr("Cancel"),this);

    connect(valueLineEdit,SIGNAL(textChanged(QString)),this,SLOT(valueEdited(QString)));
    connect(samplingSlider,SIGNAL(valueChanged(int)),this,SLOT(valueEdited(int)));
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

    layout->addWidget(samplingLabel,3,0,1,2, Qt::AlignRight);
    layout->addWidget(valueLineEdit,3,2,1,1);
    layout->addWidget(samplingSlider,4,1,1,2);

    layout->addWidget(cancelBtn,5,0,1,2, Qt::AlignBottom | Qt::AlignLeft);
    layout->addWidget(searchBtn,5,2,1,2, Qt::AlignBottom | Qt::AlignRight);

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

void CurrentSearchDialog::valueEdited(QString value)
{
    valueLineEdit->setText(value);
}

void CurrentSearchDialog::valueEdited(int value)
{
    samplingValue = qPow(2, value);
    valueEdited(QString::number(samplingValue));
}

