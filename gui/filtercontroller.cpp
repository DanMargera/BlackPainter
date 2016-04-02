#include "filtercontroller.h"
#include "pidtools.h"
#include <QDebug>

void FilterController::execBinaring(QImage image)
{
    restore = image;
    modified = image;

    thresholdFilterDialog = new ThresholdFilterDialog(parent);
    connect(thresholdFilterDialog,SIGNAL(rejected()),this,SLOT(canceled()));
    connect(thresholdFilterDialog,SIGNAL(accepted()),this,SLOT(applied()));
    connect(thresholdFilterDialog,SIGNAL(changed(QString)),this,SLOT(changed(QString)));

    thresholdFilterDialog->showNormal();

    modified = PIDTools::threshold(restore,thresholdFilterDialog->getValue());
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

void FilterController::execBrightnessContrast(QImage image)
{
    restore = image;
    modified = image;

    brightnessContrastFilterDialog = new BrightnessContrastFilterDialog(parent);
    connect(brightnessContrastFilterDialog,SIGNAL(rejected()),this,SLOT(canceled()));
    connect(brightnessContrastFilterDialog,SIGNAL(accepted()),this,SLOT(applied()));
    connect(brightnessContrastFilterDialog,SIGNAL(changed(QString)),this,SLOT(changed(QString)));

    brightnessContrastFilterDialog->showNormal();

    modified = PIDTools::brightnessContrast(restore,
                                    brightnessContrastFilterDialog->getBrightness(),
                                    brightnessContrastFilterDialog->getContrast()/100.0+1.0);
    filterChanged(modified);
}

void FilterController::changed(QString filter)
{
    if(filter == ThresholdFilterDialog::FILTER)
        modified = PIDTools::threshold(restore,thresholdFilterDialog->getValue());
    else if(filter == LevelsFilterDialog::FILTER)
        modified = PIDTools::RGB_Level(restore,
                                        levelsFilterDialog->getLowValue(),
                                        levelsFilterDialog->getHighValue());
    else if(filter == BrightnessContrastFilterDialog::FILTER)
        modified = PIDTools::brightnessContrast(restore,
                                        brightnessContrastFilterDialog->getBrightness(),
                                        brightnessContrastFilterDialog->getContrast()/100.0+1.0);

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
