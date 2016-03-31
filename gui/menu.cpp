#include "menu.h"

Menu::Menu(QWidget * parent)
    : QMenuBar(parent)
{
    createMenuBar();
}



void Menu::createMenuBar()
{
    fileMenu = new QMenu(tr("&File"), this);
    addMenu(fileMenu);

    editMenu = new QMenu(tr("&Edit"), this);
    addMenu(editMenu);

    drawMenu = new QMenu(tr("&Draw"), this);
    addMenu(drawMenu);

    viewMenu = new QMenu(tr("&View"), this);
    addMenu(viewMenu);

    helpMenu = new QMenu(tr("&Help"), this);
    addMenu(helpMenu);
}
