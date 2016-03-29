#ifndef MENU_H
#define MENU_H

#include <QMenuBar>

class Menu : public QMenuBar
{
    Q_OBJECT

public:
    Menu(QWidget * parent = 0);

private:
    void createActions();
    void createMenuBar();

public:
    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *drawMenu;
    QMenu *viewMenu;
    QMenu *helpMenu;
};

#endif // MENU_H
