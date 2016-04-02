#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include <QWidget>
#include <QVector>
#include <QMouseEvent>
#include <pidtools.h>

class Histogram : public QWidget
{
    Q_OBJECT

public:
    Histogram(QWidget * parent);
    void setRGBHistogram(RGB_Data* vector);
    RGB_Data* getRGBHistogram() { return vector; }

protected:

    void paintEvent(QPaintEvent * event);
    QPointF translate(qreal x, qreal y);
    void mouseDoubleClickEvent(QMouseEvent * event);
    qreal xMax;
    qreal yMax;

private:
    RGB_Data* vector;

signals:
	void mouseDoubleClick();

};

#endif // HISTOGRAM_H
