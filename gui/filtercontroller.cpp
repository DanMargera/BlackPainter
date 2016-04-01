#include "filtercontroller.h"
#include "pidtools.h"

void FilterController::execBinaring(QImage image)
{
    restore = image;
    modified = image;

    BinaringFilterDialog * binaringFilterDialog = new BinaringFilterDialog(parent);
    connect(binaringFilterDialog,SIGNAL(rejected()),this,SLOT(canceled()));
    connect(binaringFilterDialog,SIGNAL(accepted()),this,SLOT(applied()));
    connect(binaringFilterDialog,SIGNAL(changed(int)),this,SLOT(changed(int)));

    binaringFilterDialog->showNormal();

    modified = PIDTools::binaring(restore,binaringFilterDialog->getValue());
    filterChanged(modified);
}

void FilterController::changed(int arg0)
{
    modified = PIDTools::binaring(restore,arg0);
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
