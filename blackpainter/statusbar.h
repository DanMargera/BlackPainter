#ifndef STATUSBAR_H
#define STATUSBAR_H

#include <QStatusBar>
#include <QLabel>

class StatusBar : public QStatusBar
{
public:
    StatusBar(QWidget * parent = 0);
    ~StatusBar();

    void setMouseTrackingLabel(QString pos) { mouseTrackingLabel->setText(pos); }
    void setToolTrackingLabel(QString tool) { toolTrackingLabel->setText(tool); }
    void setZoomLabel(QString zoom)         { zoomLabel->setText(zoom);         }
    QLabel* getMouseTrackingLabel()         { return mouseTrackingLabel;        }
    QLabel* getToolTrackingLabel()          { return toolTrackingLabel;         }
    QLabel* getZoomLabel()                  { return zoomLabel;                 }

private:
    QLabel* mouseTrackingLabel;
    QLabel* toolTrackingLabel;
    QLabel* zoomLabel;
};

#endif // STATUSBAR_H
