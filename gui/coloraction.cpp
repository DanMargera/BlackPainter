#include <QColorDialog>

#include "coloraction.h"

ColorAction::ColorAction(QSize iconSize, QColor color, const QString & text, QObject * parent)
    : QAction(text,parent),  iconSize(iconSize), color(color)
{
    setColor(color);
    connect(this,SIGNAL(triggered(bool)),this,SLOT(colorChooser()));
}

void ColorAction::colorChooser()
{
    color = QColorDialog::getColor(color);
    setColor(color);
}

void ColorAction::setColor(QColor color)
{
    QPixmap pixmap(iconSize.width(),iconSize.height());
    pixmap.fill(color);
    setIcon(QIcon(pixmap));
}

QColor ColorAction::getColor()
{
    return color;
}

