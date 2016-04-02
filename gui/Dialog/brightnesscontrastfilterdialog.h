#ifndef BRIGHTNESSCONTRASTFILTERDIALOG_H
#define BRIGHTNESSCONTRASTFILTERDIALOG_H

#include <QSlider>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QDialog>
#include <QImage>

class BrightnessContrastFilterDialog : public QDialog
{
    Q_OBJECT

public:
    BrightnessContrastFilterDialog(QWidget * parent = 0);

    static QString FILTER;

    int getBrightness() { return brightnessValue;  }
    int getContrast()   { return contrastValue; }

signals:
    void changed(QString filter);
    void ok();
    void cancel();

private:

    int brightnessMax;
    int brightnessMin;
    int contrastMax;
    int contrastMin;
    int brightnessValue;
    int contrastValue;

    QLabel      *brightnessContrastLabel;
    QLabel      *brightnessLabel;
    QLabel      *contrastLabel;
    QLineEdit   *brightnessLineEdit;
    QLineEdit   *contrastLineEdit;
    QSlider     *brightnessSlider;
    QSlider     *contrastSlider;
    QPushButton *okBtn;
    QPushButton *cancelBtn;

    void createLayout();
    void createWidgets();

private slots:
    void okBrightnessContrast();
    void cancelBrightnessContrast();
    void brightnessEdited(QString value);
    void brightnessEdited(int value);
    void contrastEdited(QString value);
    void contrastEdited(int value);
};


#endif // BRIGHTNESSCONTRASTFILTERDIALOG_H
