#ifndef BINARINGFILTERDIALOG_H
#define BINARINGFILTERDIALOG_H

#include <QSlider>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QDialog>

class BinaringFilterDialog : public QDialog
{
    Q_OBJECT

public:
    BinaringFilterDialog(QWidget * parent = 0);

signals:
    void changed(int value);
    void ok();
    void cancel();

private:

    int max;
    int min;
    int value;

    QLabel      *binaringLabel;
    QLineEdit   *valueLineEdit;
    QSlider     *binaringSlider;
    QPushButton *okBtn;
    QPushButton *cancelBtn;

    void createLayout();
    void createWidgets();

private slots:
    void okBinaring();
    void cancelBinaring();
    void valueEdited(QString value);
    void valueEdited(int value);
};

#endif // BINARINGFILTERDIALOG_H