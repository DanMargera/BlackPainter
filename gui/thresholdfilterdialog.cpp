#include "thresholdfilterdialog.h"
#include <QBoxLayout>
#include <QIntValidator>
#include <QDebug>

QString ThresholdFilterDialog::FILTER = "threshold";

ThresholdFilterDialog::ThresholdFilterDialog(QWidget * parent)
    : QDialog(parent)
{
    max = 255;
    min = 0;
    value = 128;

    createWidgets();
    createLayout();
}

void ThresholdFilterDialog::createWidgets()
{
    thresholdLabel = new QLabel(tr("Choose the threshold value:"),this);

    thresholdSlider   = new QSlider(this);
    valueLineEdit    = new QLineEdit(QString::number(value),this);

    valueLineEdit->setValidator(new QIntValidator(min,max,this));

    thresholdSlider->setMinimum(min);
    thresholdSlider->setMaximum(max);
    thresholdSlider->setValue(value);

    thresholdSlider->setOrientation(Qt::Horizontal);

    valueLineEdit->setMaximumWidth(40);

    okBtn      = new QPushButton(tr("Ok"),this);
    cancelBtn  = new QPushButton(tr("Cancel"),this);

    connect(valueLineEdit,SIGNAL(textChanged(QString)),this,SLOT(valueEdited(QString)));
    connect(thresholdSlider,SIGNAL(valueChanged(int)),this,SLOT(valueEdited(int)));
    connect(okBtn,SIGNAL(clicked(bool)),this,SLOT(okThreshold()));
    connect(cancelBtn,SIGNAL(clicked(bool)),this,SLOT(cancelThreshold()));

}

void ThresholdFilterDialog::createLayout()
{
    QWidget *thresholdWidget = new QWidget(this);
    QWidget *btnWidget  = new QWidget(this);

    QVBoxLayout *allLayout   = new QVBoxLayout(this);
    QHBoxLayout *thresholdLayout  = new QHBoxLayout(thresholdWidget);
    QHBoxLayout *btnLayout   = new QHBoxLayout(btnWidget);

    thresholdLayout->setSpacing(0);
    btnLayout->setSpacing(0);
    allLayout->setContentsMargins(5,5,5,5);
    thresholdLayout->setContentsMargins(0,0,0,0);
    btnLayout->setContentsMargins(0,0,0,0);


    thresholdWidget->setLayout(thresholdLayout);
    btnWidget->setLayout(btnLayout);


    allLayout->addWidget(thresholdLabel);
    allLayout->addWidget(thresholdWidget);
    allLayout->addWidget(btnWidget);

    thresholdLayout->addWidget(thresholdSlider);
    thresholdLayout->addWidget(valueLineEdit);

    btnLayout->addWidget(cancelBtn);
    btnLayout->addWidget(okBtn);

    setLayout(allLayout);
}

void ThresholdFilterDialog::valueEdited(QString value)
{
    if(value.isEmpty())
        value = QString::number(this->value);
    if(value.toInt() < min || value.toInt() > max)
        value = QString::number(this->value);
    valueLineEdit->setText(value);
    this->value = value.toInt();
    thresholdSlider->setValue(this->value);

    changed(ThresholdFilterDialog::FILTER);
}

void ThresholdFilterDialog::valueEdited(int value)
{
    valueEdited(QString::number(value));
}

void ThresholdFilterDialog::okThreshold()
{
    accept();
    close();
}

void ThresholdFilterDialog::cancelThreshold()
{
    reject();
    close();
}
