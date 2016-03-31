#include <QColorDialog>
#include <QPainter>
#include "colorbutton.h"

#define BORDER 0

ColorButton::ColorButton(QColor color, QWidget * parent)
    : QPushButton(parent), color(color)
{

    setMaximumWidth(20);
    setMaximumHeight(20);
    setFlat(true);
    connect(this,SIGNAL(clicked(bool)),this,SLOT(colorChooser()));
}

void ColorButton::colorChooser()
{
    color = QColorDialog::getColor(color);
    repaint();
}

void ColorButton::paintEvent(QPaintEvent *)
{

   QPainter painter(this);
   painter.setPen(QPen(QColor(180,180,180)));
   painter.setBrush(QBrush(color));
   painter.drawRect(QRectF(BORDER,BORDER,width()-2*BORDER,height()-2*BORDER));
}

QColor ColorButton::getColor()
{
    return color;
}
