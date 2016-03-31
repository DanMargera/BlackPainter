#include "statusbar.h"

StatusBar::StatusBar(QWidget * parent)
    : QStatusBar(parent)
{
    mouseTrackingLabel = new QLabel(this);
    toolTrackingLabel = new QLabel(this);
    zoomLabel = new QLabel(this);

    addWidget(mouseTrackingLabel,1);
    addWidget(toolTrackingLabel,1);
    addWidget(zoomLabel,1);
}

StatusBar::~StatusBar()
{
    delete mouseTrackingLabel;
    delete toolTrackingLabel;
    delete zoomLabel;
}
