#ifndef FILTERCONTROLLER_H
#define FILTERCONTROLLER_H

#include <QObject>
#include <QWidget>
#include <QImage>
#include "thresholdfilterdialog.h"
#include "levelsfilterdialog.h"
#include "brightnesscontrastfilterdialog.h"


class FilterController : public QObject
{
    Q_OBJECT

public:
    FilterController(QWidget * parent = 0)
    {
        this->parent = parent;
    }
    void execBinaring(QImage image);
    void execLevels(QImage image);
    void execBrightnessContrast(QImage image);

public slots:
    void changed(QString filter);
    void applied();
    void canceled();

private:
    QWidget * parent;

    QImage restore;
    QImage modified;

    // FIlters
    ThresholdFilterDialog*          thresholdFilterDialog;
    LevelsFilterDialog*             levelsFilterDialog;
    BrightnessContrastFilterDialog* brightnessContrastFilterDialog;

signals:
    void filterChanged(QImage image);
    void filterApplied(QImage image);
    void filterCanceled(QImage image);
};

#endif // FILTERCONTROLLER_H
