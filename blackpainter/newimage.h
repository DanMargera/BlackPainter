#ifndef NEWIMAGE_H
#define NEWIMAGE_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QColor>
#include "colorbutton.h"

class NewImage : public QDialog
{
    Q_OBJECT

public:
    NewImage(QWidget * parent = 0, int width = 400, int height = 400);
    QSize selectedSize();
    QColor selectedColor();


private:
    QLabel*      dialogLabel;

    QLabel*      widthLabel;
    QLabel*      widthUnitLabel;
    QLineEdit*   widthLineEdit;

    QLabel*      heightLabel;
    QLabel*      heightUnitLabel;
    QLineEdit*   heightLineEdit;

    QLabel*      bgColorLabel;
    ColorButton* colorButton;

    QPushButton* createBtn;
    QPushButton* cancelBtn;

    void createWidgets(int width, int height);
    void createLayout();
};

#endif // NEWIMAGE_H
