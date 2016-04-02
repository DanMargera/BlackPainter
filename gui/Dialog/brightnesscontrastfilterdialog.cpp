#include "brightnesscontrastfilterdialog.h"

#include <QBoxLayout>
#include <QIntValidator>

QString BrightnessContrastFilterDialog::FILTER = "brightnessContrast";

BrightnessContrastFilterDialog::BrightnessContrastFilterDialog(QWidget * parent)
    : QDialog(parent)
{
    brightnessMax = 150;
    brightnessMin = -150;

    contrastMax = 100;
    contrastMin = -50;

    brightnessValue = 0;
    contrastValue = 0;

    createWidgets();
    createLayout();
}

void BrightnessContrastFilterDialog::createWidgets()
{
    // Cria e configura o texto descritivo
    brightnessContrastLabel = new QLabel(tr("Choose the range for values:"),this);
    brightnessLabel = new QLabel(tr("Brightness:"),this);
    contrastLabel = new QLabel(tr("Contrast:"),this);

    // Cria e configura os dois sliders
    brightnessSlider   = new QSlider(this);
    contrastSlider  = new QSlider(this);


    brightnessSlider->setMinimum(brightnessMin);
    brightnessSlider->setMaximum(brightnessMax);
    brightnessSlider->setValue(brightnessValue);
    brightnessSlider->setOrientation(Qt::Horizontal);


    contrastSlider->setMinimum(contrastMin);
    contrastSlider->setMaximum(contrastMax);
    contrastSlider->setValue(contrastValue);
    contrastSlider->setOrientation(Qt::Horizontal);

    // Cria e configura os dois campos de valores
    brightnessLineEdit  = new QLineEdit(QString::number(brightnessValue),this);
    contrastLineEdit = new QLineEdit(QString::number(contrastValue),this);

    brightnessLineEdit->setValidator(new QIntValidator(brightnessMin,brightnessMax,this));
    contrastLineEdit->setValidator(new QIntValidator(contrastMin,contrastMax,this));

    brightnessLineEdit->setMaximumWidth(40);
    contrastLineEdit->setMaximumWidth(40);

    // Cria e configura os butoes
    okBtn      = new QPushButton(tr("Ok"),this);
    cancelBtn  = new QPushButton(tr("Cancel"),this);

    // Cria as conexoes entre sinais e slots
    connect(brightnessLineEdit,SIGNAL(textChanged(QString)),this,SLOT(brightnessEdited(QString)));
    connect(contrastLineEdit,SIGNAL(textChanged(QString)),this,SLOT(contrastEdited(QString)));
    connect(brightnessSlider,SIGNAL(valueChanged(int)),this,SLOT(brightnessEdited(int)));
    connect(contrastSlider,SIGNAL(valueChanged(int)),this,SLOT(contrastEdited(int)));
    connect(okBtn,SIGNAL(clicked(bool)),this,SLOT(okBrightnessContrast()));
    connect(cancelBtn,SIGNAL(clicked(bool)),this,SLOT(cancelBrightnessContrast()));
}

void BrightnessContrastFilterDialog::createLayout()
{
    // Constroi layout dos seletores de valores
    QWidget *brightnessWidget       = new QWidget(this);
    QWidget *contrastWidget      = new QWidget(this);
    QHBoxLayout *brightnessLayout   = new QHBoxLayout(brightnessWidget);
    QHBoxLayout *contrastLayout = new QHBoxLayout(contrastWidget);

    brightnessLayout->setSpacing(0);
    contrastLayout->setSpacing(0);

    brightnessLayout->setContentsMargins(0,0,0,0);
    contrastLayout->setContentsMargins(0,0,0,0);

    brightnessWidget->setLayout(brightnessLayout);
    contrastWidget->setLayout(contrastLayout);

    brightnessLayout->addWidget(brightnessSlider);
    contrastLayout->addWidget(contrastSlider);

    brightnessLayout->addWidget(brightnessLineEdit);
    contrastLayout->addWidget(contrastLineEdit);

    // Constroi layout dos botoes
    QWidget *btnWidget     = new QWidget(this);
    QHBoxLayout *btnLayout = new QHBoxLayout(btnWidget);

    btnLayout->setSpacing(0);
    btnLayout->setContentsMargins(0,0,0,0);
    btnWidget->setLayout(btnLayout);

    btnLayout->addWidget(cancelBtn);
    btnLayout->addWidget(okBtn);

    // Constroi o layout do Dialog
    QVBoxLayout *allLayout = new QVBoxLayout(this);

    allLayout->setContentsMargins(5,5,5,5);
    allLayout->addWidget(brightnessContrastLabel);
    allLayout->addWidget(brightnessLabel);
    allLayout->addWidget(brightnessWidget);
    allLayout->addWidget(contrastLabel);
    allLayout->addWidget(contrastWidget);
    allLayout->addWidget(btnWidget);

    // Aplica o layout ao Dialog
    setLayout(allLayout);
}

void BrightnessContrastFilterDialog::brightnessEdited(QString value)
{
    if(value.isEmpty())
        value = QString::number(brightnessValue);
    if(value.toInt() < brightnessMin || value.toInt() > brightnessMax)
        value = QString::number(brightnessValue);
    brightnessLineEdit->setText(value);
    brightnessValue = value.toInt();
    brightnessSlider->setValue(brightnessValue);

    changed(BrightnessContrastFilterDialog::FILTER);
}

void BrightnessContrastFilterDialog::brightnessEdited(int value)
{
    brightnessEdited(QString::number(value));
}

void BrightnessContrastFilterDialog::contrastEdited(QString value)
{
    if(value.isEmpty())
        value = QString::number(contrastValue);
    if(value.toInt() < contrastMin || value.toInt() > contrastMax)
        value = QString::number(contrastValue);
    contrastLineEdit->setText(value);
    contrastValue = value.toInt();
    contrastSlider->setValue(contrastValue);

    changed(BrightnessContrastFilterDialog::FILTER);
}

void BrightnessContrastFilterDialog::contrastEdited(int value)
{
    contrastEdited(QString::number(value));
}

void BrightnessContrastFilterDialog::okBrightnessContrast()
{
    accept();
    close();
}

void BrightnessContrastFilterDialog::cancelBrightnessContrast()
{
    reject();
    close();
}


