#include "levelsfilterdialog.h"
#include <QBoxLayout>
#include <QIntValidator>

QString LevelsFilterDialog::FILTER = "levels";

LevelsFilterDialog::LevelsFilterDialog(QWidget * parent)
    : QDialog(parent)
{
    max = 255;
    min = 0;
    lowValue = 0;
    highValue = 255;

    createWidgets();
    createLayout();
}

void LevelsFilterDialog::createWidgets()
{
    // Cria e configura o texto descritivo
    levelsLabel = new QLabel(tr("Choose the range for values:"),this);

    // Cria e configura os dois sliders
    lowLevelsSlider   = new QSlider(this);
    highLevelsSlider  = new QSlider(this);


    lowLevelsSlider->setMinimum(min);
    lowLevelsSlider->setMaximum(max);
    lowLevelsSlider->setValue(lowValue);
    lowLevelsSlider->setOrientation(Qt::Horizontal);


    highLevelsSlider->setMinimum(min);
    highLevelsSlider->setMaximum(max);
    highLevelsSlider->setValue(0);
    highLevelsSlider->setInvertedAppearance(true);
    highLevelsSlider->setOrientation(Qt::Horizontal);

    // Cria e configura os dois campos de valores
    lowValueLineEdit  = new QLineEdit(QString::number(lowValue),this);
    highValueLineEdit = new QLineEdit(QString::number(highValue),this);

    lowValueLineEdit->setValidator(new QIntValidator(min,max,this));
    highValueLineEdit->setValidator(new QIntValidator(min,max,this));

    lowValueLineEdit->setMaximumWidth(40);
    highValueLineEdit->setMaximumWidth(40);

    // Cria e configura os butoes
    okBtn      = new QPushButton(tr("Ok"),this);
    cancelBtn  = new QPushButton(tr("Cancel"),this);

    // Cria as conexoes entre sinais e slots
    connect(lowValueLineEdit,SIGNAL(textChanged(QString)),this,SLOT(lowValueEdited(QString)));
    connect(highValueLineEdit,SIGNAL(textChanged(QString)),this,SLOT(highValueEdited(QString)));
    connect(lowLevelsSlider,SIGNAL(valueChanged(int)),this,SLOT(lowValueEdited(int)));
    connect(highLevelsSlider,SIGNAL(valueChanged(int)),this,SLOT(highValueEdited(int)));
    connect(okBtn,SIGNAL(clicked(bool)),this,SLOT(okLevels()));
    connect(cancelBtn,SIGNAL(clicked(bool)),this,SLOT(cancelLevels()));
}

void LevelsFilterDialog::createLayout()
{
    // Constroi layout dos seletores de valores
    QWidget *lowLevelsWidget       = new QWidget(this);
    QWidget *highLevelsWidget      = new QWidget(this);
    QHBoxLayout *lowLevelsLayout   = new QHBoxLayout(lowLevelsWidget);
    QHBoxLayout *highLevelsLayout = new QHBoxLayout(highLevelsWidget);

    lowLevelsLayout->setSpacing(0);
    highLevelsLayout->setSpacing(0);

    lowLevelsLayout->setContentsMargins(0,0,0,0);
    highLevelsLayout->setContentsMargins(0,0,0,0);

    lowLevelsWidget->setLayout(lowLevelsLayout);
    highLevelsWidget->setLayout(highLevelsLayout);

    lowLevelsLayout->addWidget(lowLevelsSlider);
    highLevelsLayout->addWidget(highLevelsSlider);

    lowLevelsLayout->addWidget(lowValueLineEdit);
    highLevelsLayout->addWidget(highValueLineEdit);

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
    allLayout->addWidget(levelsLabel);
    allLayout->addWidget(lowLevelsWidget);
    allLayout->addWidget(highLevelsWidget);
    allLayout->addWidget(btnWidget);

    // Aplica o layout ao Dialog
    setLayout(allLayout);
}

void LevelsFilterDialog::lowValueEdited(QString value)
{
    if(value.isEmpty())
        value = QString::number(lowValue);
    if(value.toInt() < min || value.toInt() > max)
        value = QString::number(lowValue);
    lowValueLineEdit->setText(value);
    lowValue = value.toInt();
    lowLevelsSlider->setValue(lowValue);

    changed(LevelsFilterDialog::FILTER);
}

void LevelsFilterDialog::lowValueEdited(int value)
{
    lowValueEdited(QString::number(value));
}

void LevelsFilterDialog::highValueEdited(QString value)
{
    if(value.isEmpty())
        value = QString::number(highValue);
    if(value.toInt() < min || value.toInt() > max)
        value = QString::number(highValue);
    highValueLineEdit->setText(value);
    highValue = value.toInt();
    highLevelsSlider->setValue(max-highValue);

    changed(LevelsFilterDialog::FILTER);
}

void LevelsFilterDialog::highValueEdited(int value)
{
    highValueEdited(QString::number(max - value));
}

void LevelsFilterDialog::okLevels()
{
    accept();
    close();
}

void LevelsFilterDialog::cancelLevels()
{
    reject();
    close();
}

