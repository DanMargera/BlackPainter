#ifndef FILTERCONTROLLER_H
#define FILTERCONTROLLER_H

#include <QObject>
#include <QWidget>
#include <QImage>
#include "binaringfilterdialog.h"

class FilterController : public QObject
{
    Q_OBJECT

public:
    FilterController(QWidget * parent = 0)
    {
        this->parent = parent;
    }
    void execBinaring(QImage image);

public slots:
    void changed(int arg0);
    void applied();
    void canceled();

private:
    QWidget * parent;

    QImage restore;
    QImage modified;

signals:
    void filterChanged(QImage image);
    void filterApplied(QImage image);
    void filterCanceled(QImage image);
};

#endif // FILTERCONTROLLER_H
