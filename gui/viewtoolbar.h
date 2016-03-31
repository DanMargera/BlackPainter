#ifndef VIEWTOOLBAR_H
#define VIEWTOOLBAR_H

#include <QToolBar>
#include <QToolButton>
#include <QSlider>

class ViewToolbar : public QToolBar
{
    Q_OBJECT

public:
    ViewToolbar(QWidget * parent = 0);

private:
    void createToolButtons();

};

#endif // VIEWTOOLBAR_H
