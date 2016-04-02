#ifndef COLORBUTTON_H
#define COLORBUTTON_H

#include <QPushButton>
#include <QColor>
#include <QSize>

class ColorButton : public QPushButton
{
    Q_OBJECT

public:
    ColorButton(QColor color, QWidget * parent);
    QColor getColor();

protected:
    void paintEvent(QPaintEvent *);
private:
    QColor color;

private slots:
    void colorChooser();

};

#endif // COLORBUTTON_H
