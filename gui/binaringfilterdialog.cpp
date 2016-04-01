#include "binaringfilterdialog.h"
#include <QBoxLayout>
#include <QIntValidator>
#include <QDebug>

QString BinaringFilterDialog::FILTER = "binaring";

BinaringFilterDialog::BinaringFilterDialog(QWidget * parent)
    : QDialog(parent)
{
    max = 255;
    min = 0;
    value = 128;

    createWidgets();
    createLayout();
}

void BinaringFilterDialog::createWidgets()
{
    binaringLabel = new QLabel(tr("Choose the binaring value:"),this);

    binaringSlider   = new QSlider(this);
    valueLineEdit    = new QLineEdit(QString::number(value),this);

    valueLineEdit->setValidator(new QIntValidator(min,max,this));

    binaringSlider->setValue(value);
    binaringSlider->setMinimum(min);
    binaringSlider->setMaximum(max);

    binaringSlider->setOrientation(Qt::Horizontal);

    valueLineEdit->setMaximumWidth(40);

    okBtn      = new QPushButton(tr("Ok"),this);
    cancelBtn  = new QPushButton(tr("Cancel"),this);

    connect(valueLineEdit,SIGNAL(textChanged(QString)),this,SLOT(valueEdited(QString)));
    connect(binaringSlider,SIGNAL(valueChanged(int)),this,SLOT(valueEdited(int)));
    connect(okBtn,SIGNAL(clicked(bool)),this,SLOT(okBinaring()));
    connect(cancelBtn,SIGNAL(clicked(bool)),this,SLOT(cancelBinaring()));

}

void BinaringFilterDialog::createLayout()
{
    QWidget *binaringWidget = new QWidget(this);
    QWidget *btnWidget  = new QWidget(this);

    QVBoxLayout *allLayout   = new QVBoxLayout(this);
    QHBoxLayout *binaringLayout  = new QHBoxLayout(binaringWidget);
    QHBoxLayout *btnLayout   = new QHBoxLayout(btnWidget);

    binaringLayout->setSpacing(0);
    btnLayout->setSpacing(0);
    allLayout->setContentsMargins(5,5,5,5);
    binaringLayout->setContentsMargins(0,0,0,0);
    btnLayout->setContentsMargins(0,0,0,0);


    binaringWidget->setLayout(binaringLayout);
    btnWidget->setLayout(btnLayout);


    allLayout->addWidget(binaringLabel);
    allLayout->addWidget(binaringWidget);
    allLayout->addWidget(btnWidget);

    binaringLayout->addWidget(binaringSlider);
    binaringLayout->addWidget(valueLineEdit);

    btnLayout->addWidget(cancelBtn);
    btnLayout->addWidget(okBtn);

    setLayout(allLayout);
}

void BinaringFilterDialog::valueEdited(QString value)
{
    if(value.isEmpty())
        value = QString::number(this->value);
    if(value.toInt() < min || value.toInt() > max)
        value = QString::number(this->value);
    valueLineEdit->setText(value);
    this->value = value.toInt();
    binaringSlider->setValue(this->value);

    changed(BinaringFilterDialog::FILTER);
}

void BinaringFilterDialog::valueEdited(int value)
{
    valueEdited(QString::number(value));
}

void BinaringFilterDialog::okBinaring()
{
    accept();
    close();
}

void BinaringFilterDialog::cancelBinaring()
{
    reject();
    close();
}
