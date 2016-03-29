#include "preferences.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>

Preferences::Preferences(QWidget * parent)
    : QDialog(parent)
{
    setMinimumWidth(400);
    createWidgets();
    createLayout();
}

void Preferences::createWidgets()
{
    imagePahtLabel = new QLabel(tr("Choose the image bank folder:"),this);

    pathLineEdit   = new QLineEdit(tr(""),this);
    choosePathBtn  = new QPushButton("...",this);

    choosePathBtn->setMaximumWidth(30);

    applyPathBtn   = new QPushButton(tr("Apply"),this);
    okPathBtn      = new QPushButton(tr("Ok"),this);
    cancelPathBtn  = new QPushButton(tr("Cancel"),this);

    applyPathBtn->setDisabled(true);

    connect(choosePathBtn,SIGNAL(clicked(bool)),this,SLOT(choosePath()));
    connect(applyPathBtn, SIGNAL(clicked(bool)),this,SLOT(applyPath()));
    connect(okPathBtn,    SIGNAL(clicked(bool)),this,SLOT(okPath()));
    connect(cancelPathBtn,SIGNAL(clicked(bool)),this,SLOT(cancelPath()));
    connect(pathLineEdit,SIGNAL(textChanged(QString)),this,SLOT(updateBtns()));
}

void Preferences::createLayout()
{
    QWidget *pathWidget = new QWidget(this);
    QWidget *btnWidget  = new QWidget(this);


    QVBoxLayout *allLayout   = new QVBoxLayout(this);
    QHBoxLayout *pathLayout  = new QHBoxLayout(pathWidget);
    QHBoxLayout *btnLayout   = new QHBoxLayout(btnWidget);

    pathLayout->setSpacing(0);
    btnLayout->setSpacing(0);
    allLayout->setContentsMargins(5,5,5,5);
    pathLayout->setContentsMargins(0,0,0,0);
    btnLayout->setContentsMargins(0,0,0,0);


    pathWidget->setLayout(pathLayout);
    btnWidget->setLayout(btnLayout);


    allLayout->addWidget(imagePahtLabel);
    allLayout->addWidget(pathWidget);
    allLayout->addWidget(btnWidget);

    pathLayout->addWidget(pathLineEdit);
    pathLayout->addWidget(choosePathBtn);

    btnLayout->addWidget(cancelPathBtn);
    btnLayout->addWidget(okPathBtn);
    btnLayout->addWidget(applyPathBtn);

    setLayout(allLayout);
}

void Preferences::choosePath()
{
    QFileDialog openDialog(this);
    openDialog.setFileMode(QFileDialog::Directory);
    if(!openDialog.exec()) return;

    pathLineEdit->setText(openDialog.selectedFiles().at(0));
}

void Preferences::applyPath()
{
    applyPathBtn->setDisabled(true);
    apply();
}

void Preferences::okPath()
{
    if(applyPathBtn->isEnabled()) apply();
    close();
}

void Preferences::cancelPath()
{
    cancel();
    close();
}

QString Preferences::getPath()
{
    return pathLineEdit->text();
}

void Preferences::setPath(QString path)
{
    pathLineEdit->setText(path);
}

void Preferences::updateBtns()
{
    applyPathBtn->setDisabled(false);
}

Preferences::~Preferences()
{
    delete imagePahtLabel;

    delete pathLineEdit;
    delete choosePathBtn;

    delete applyPathBtn;
    delete okPathBtn;
    delete cancelPathBtn;
}




