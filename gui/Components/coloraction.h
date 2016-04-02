#ifndef COLORACTION_H
#define COLORACTION_H

#include <QAction>
#include <QColor>
#include <QSize>

class ColorAction : public QAction
{
    Q_OBJECT

public:
    ColorAction(QSize iconSize, QColor color, const QString & text, QObject * parent);
    void setColor(QColor color);
    QColor getColor();
private:
    QColor color;
    QSize iconSize;

private slots:
    void colorChooser();

};

#endif // COLORACTION_H
