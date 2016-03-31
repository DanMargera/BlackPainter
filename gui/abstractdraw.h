#ifndef ABSTRACTDRAW_H
#define ABSTRACTDRAW_H

#include <QObject>
#include <QMouseEvent>
#include <QGraphicsView>

class AbstractDraw : public QObject
{
    Q_OBJECT

public:
    virtual void draw(QMouseEvent *event, QGraphicsView* view) = 0;

    QColor getBorderColor ()             { return borderColor;  }
    QColor getFillColor   ()             { return fillColor;    }
    void   setBorderColor (QColor color) { borderColor = color; }
    void   setBorderWidth (int width   ) { borderWidth = width; }
    void   setFillColor   (QColor color) { fillColor = color;   }

signals:
    void   toolTracking   (QString string);

protected:
    QColor borderColor;
    QColor fillColor;
    int borderWidth;
};

#endif // ABSTRACTDRAW_H
