#ifndef BINARINGFILTERDIALOG_H
#define BINARINGFILTERDIALOG_H

#include <QSlider>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QDialog>
#include <QImage>

class ThresholdFilterDialog : public QDialog
{
    Q_OBJECT

public:
    ThresholdFilterDialog(QWidget * parent = 0);

    int getValue() { return value; }

    static QString FILTER;

signals:
    void changed(QString filter);
    void ok();
    void cancel();

private:

    int max;
    int min;
    int value;

    QLabel      *thresholdLabel;
    QLineEdit   *valueLineEdit;
    QSlider     *thresholdSlider;
    QPushButton *okBtn;
    QPushButton *cancelBtn;

    void createLayout();
    void createWidgets();

private slots:
    void okThreshold();
    void cancelThreshold();
    void valueEdited(QString value);
    void valueEdited(int value);
};

#endif // BINARINGFILTERDIALOG_H
