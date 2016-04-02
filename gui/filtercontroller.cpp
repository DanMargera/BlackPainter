#include "filtercontroller.h"
#include "pidtools.h"
#include <QDebug>

void FilterController::execBinaring(QImage image)
{
    restore = image;
    modified = image;

    binaringFilterDialog = new BinaringFilterDialog(parent);
    connect(binaringFilterDialog,SIGNAL(rejected()),this,SLOT(canceled()));
    connect(binaringFilterDialog,SIGNAL(accepted()),this,SLOT(applied()));
    connect(binaringFilterDialog,SIGNAL(changed(QString)),this,SLOT(changed(QString)));

    binaringFilterDialog->showNormal();

    modified = PIDTools::binaring(restore,binaringFilterDialog->getValue());
    filterChanged(modified);
}

void FilterController::execLevels(QImage image)
{
    restore = image;
    modified = image;

    levelsFilterDialog = new LevelsFilterDialog(parent);
    connect(levelsFilterDialog,SIGNAL(rejected()),this,SLOT(canceled()));
    connect(levelsFilterDialog,SIGNAL(accepted()),this,SLOT(applied()));
    connect(levelsFilterDialog,SIGNAL(changed(QString)),this,SLOT(changed(QString)));

    levelsFilterDialog->showNormal();

    modified = PIDTools::RGB_Level(restore,
                                    levelsFilterDialog->getLowValue(),
                                    levelsFilterDialog->getHighValue());
    filterChanged(modified);
}

void FilterController::changed(QString filter)
{
    if(filter == BinaringFilterDialog::FILTER)
        modified = PIDTools::binaring(restore,binaringFilterDialog->getValue());
    else if(filter == LevelsFilterDialog::FILTER)
        modified = PIDTools::RGB_Level(restore,
                                        levelsFilterDialog->getLowValue(),
                                        levelsFilterDialog->getHighValue());


    filterChanged(modified);
}

void FilterController::applied()
{
    filterApplied(modified);
}

void FilterController::canceled()
{
    filterCanceled(restore);
}
