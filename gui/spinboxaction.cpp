#include "spinboxaction.h"
#include <QDebug>
#include <QToolBar>
#include <QHBoxLayout>
#include <QDebug>

SpinBoxAction::SpinBoxAction(QObject * parent, int value)
    : QWidgetAction(parent)
{
    validator = new QIntValidator(this);
    this->value = value;

    toolBarWidget        = new QWidget();
    menuWidget           = new QWidget();

    menuTextLabel        = new QLabel     (menuWidget);
    menuValueLineEdit    = new QLineEdit  (menuWidget);
    menuIncreaseBtn      = new QPushButton(menuWidget);
    menuDicreaseBtn      = new QPushButton(menuWidget);

    toolBarValueLineEdit = new QLineEdit  (toolBarWidget);
    toolBarIncreaseBtn   = new QPushButton(toolBarWidget);
    toolBarDicreaseBtn   = new QPushButton(toolBarWidget);

    menuValueLineEdit->setValidator(new QIntValidator(this));
    toolBarValueLineEdit->setValidator(new QIntValidator(this));

    connect(menuIncreaseBtn,   SIGNAL(clicked(bool)),this,SLOT(increase()));
    connect(toolBarIncreaseBtn,SIGNAL(clicked(bool)),this,SLOT(increase()));
    connect(menuDicreaseBtn,   SIGNAL(clicked(bool)),this,SLOT(dicrease()));
    connect(toolBarDicreaseBtn,SIGNAL(clicked(bool)),this,SLOT(dicrease()));

    connect(menuValueLineEdit,SIGNAL(textEdited(QString)),this,SLOT(setValue(QString)));
    connect(toolBarValueLineEdit,SIGNAL(textEdited(QString)),this,SLOT(setValue(QString)));

    //ToolBar
    QVBoxLayout* toolBarLayout = new QVBoxLayout(toolBarWidget);

    toolBarLayout->setContentsMargins(0,0,0,0);
    toolBarLayout->setSpacing(0);
    toolBarLayout->setMargin(0);

    toolBarValueLineEdit->setAlignment(Qt::AlignRight);
    toolBarValueLineEdit->setMaximumWidth(35);
    toolBarIncreaseBtn->setMaximumWidth(35);
    toolBarDicreaseBtn->setMaximumWidth(35);
    toolBarIncreaseBtn->setMaximumHeight(20);
    toolBarDicreaseBtn->setMaximumHeight(20);
    toolBarIncreaseBtn->setIcon(QIcon(":/icons/up-arrow.png"));
    toolBarDicreaseBtn->setIcon(QIcon(":/icons/down-arrow.png"));
    toolBarIncreaseBtn->setFlat(true);
    toolBarDicreaseBtn->setFlat(true);
    toolBarValueLineEdit->setAlignment(Qt::AlignCenter);

    toolBarLayout->addWidget(toolBarIncreaseBtn  );
    toolBarLayout->addWidget(toolBarValueLineEdit);
    toolBarLayout->addWidget(toolBarDicreaseBtn  );

    toolBarWidget->setLayout(toolBarLayout);

    //Menu
    QHBoxLayout* menuBarLayout = new QHBoxLayout(menuWidget);
    menuWidget->setContentsMargins(10,3,10,3);

    menuWidget->setMaximumHeight(30);
    menuBarLayout->setContentsMargins(0,0,0,0);
    menuBarLayout->setSpacing(0);
    menuBarLayout->setMargin(0);

    menuIncreaseBtn->setIcon(QIcon(":/icons/right-arrow.png"));
    menuDicreaseBtn->setIcon(QIcon(":/icons/left-arrow.png"));
    menuIncreaseBtn->setFlat(true);
    menuDicreaseBtn->setFlat(true);

    menuValueLineEdit->setMaximumWidth(40);
    menuIncreaseBtn->setMaximumWidth(30);
    menuDicreaseBtn->setMaximumWidth(30);
    menuValueLineEdit->setAlignment(Qt::AlignCenter);


    menuBarLayout->addWidget(menuTextLabel);
    menuBarLayout->addWidget(menuDicreaseBtn);
    menuBarLayout->addWidget(menuValueLineEdit);
    menuBarLayout->addWidget(menuIncreaseBtn);

    menuWidget->setLayout(menuBarLayout);
}

QWidget* SpinBoxAction::createWidget(QWidget * parent)
{
    if(!QString(parent->metaObject()->className()).compare("QToolBar"))
    {
        toolBarWidget->setVisible(isVisible());
        toolBarWidget->setParent(parent);
        return toolBarWidget;
    }
    if(!QString(parent->metaObject()->className()).compare("QMenu"))
    {
        menuWidget->setVisible(isVisible());
        menuWidget->setParent(parent);
        return menuWidget;
    }

    qDebug() << "Erro ao criar SpinBoxAction";

    return new QWidget(parent);
}

void SpinBoxAction::setText(const QString &text)
{
    QWidgetAction::setText(text);
    menuTextLabel->setText(text);
}

void SpinBoxAction::increase()
{
    setValue(value+1 > max ? max : value+1);
}

void SpinBoxAction::dicrease()
{
    setValue(value-1 < min ? min : value-1);
}

void SpinBoxAction::setRange(int min, int max)
{
    this->min = min;
    this->max = max;
    validator->setRange(min,max);
}

void SpinBoxAction::setValue(int value)
{
    setValue(QString::number(value));
}

void SpinBoxAction::setValue(QString value)
{
    if(value.isEmpty())
        value = QString::number(this->value);
    if(value.toInt() < min || value.toInt() > max)
        value = QString::number(this->value);
    menuValueLineEdit->setText(value);
    toolBarValueLineEdit->setText(value);
    this->value = value.toInt();
    this->triggered(true);

    toolBarIncreaseBtn->setDisabled(this->value == max);
    menuIncreaseBtn->setDisabled(this->value == max);
    toolBarDicreaseBtn->setDisabled(this->value == min);
    menuDicreaseBtn->setDisabled(this->value == min);
}

int SpinBoxAction::getValue()
{
    return value;
}
