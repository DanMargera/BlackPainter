#include <QGridLayout>
#include <QIntValidator>
#include "newimage.h"

NewImage::NewImage(QWidget * parent, int width, int height)
    : QDialog(parent)
{
    setMaximumSize(QSize(180,180));
    setMinimumSize(QSize(180,180));
    setWindowTitle(tr("New Image"));

    createWidgets(width,height);
    createLayout();
}

void NewImage::createWidgets(int width, int height)
{
    dialogLabel     = new QLabel      (tr("Image size:"),this);

    widthLabel      = new QLabel      (tr("Width: "),this);
    widthUnitLabel  = new QLabel      ("px",this);
    widthLineEdit   = new QLineEdit   (QString::number(width),this);

    heightLabel     = new QLabel      (tr("Height: "),this);
    heightUnitLabel = new QLabel      ("px",this);
    heightLineEdit  = new QLineEdit   (QString::number(height),this);

    bgColorLabel    = new QLabel      (tr("Background color: "),this);
    colorButton     = new ColorButton (Qt::white,this);

    createBtn       = new QPushButton (tr("Create"),this);
    cancelBtn       = new QPushButton (tr("Cancel"),this);

    widthLineEdit->setValidator(new QIntValidator(1,10000,this));
    heightLineEdit->setValidator(new QIntValidator(1,10000,this));

    connect(cancelBtn,SIGNAL(clicked(bool)),this,SLOT(close()));
    connect(createBtn,SIGNAL(clicked(bool)),this,SLOT(accept()));
}

void NewImage::createLayout()
{
    QGridLayout* layout = new QGridLayout();

    layout->addWidget(dialogLabel,0,0,1,4,Qt::AlignCenter);

    layout->addWidget(widthLabel,1,0,1,1);
    layout->addWidget(widthLineEdit,1,1,1,2);
    layout->addWidget(widthUnitLabel,1,3,1,1);

    layout->addWidget(heightLabel,2,0,1,1);
    layout->addWidget(heightLineEdit,2,1,1,2);
    layout->addWidget(heightUnitLabel,2,3,1,1);

    layout->addWidget(bgColorLabel,3,0,1,3);
    layout->addWidget(colorButton,3,3,1,1);

    layout->addWidget(cancelBtn,4,0,1,2);
    layout->addWidget(createBtn,4,2,1,2);

    setLayout(layout);
}

QSize NewImage::selectedSize()
{
    return QSize(widthLineEdit->text().toInt(),
                 heightLineEdit->text().toInt());
}

QColor NewImage::selectedColor()
{
    return colorButton->getColor();
}

