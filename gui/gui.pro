#-------------------------------------------------
#
# Project created by QtCreator 2016-03-30T23:06:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gui
TEMPLATE = app


SOURCES += \
    asyncprocess.cpp \
    binaringfilterdialog.cpp \
    coloraction.cpp \
    colorbutton.cpp \
    currentsearchdialog.cpp \
    graph.cpp \
    graphicsview.cpp \
    graphv2.cpp \
    histogram.cpp \
    imageslider.cpp \
    main.cpp \
    mainwindow.cpp \
    menu.cpp \
    multidraw.cpp \
    newimage.cpp \
    paintdraw.cpp \
    preferences.cpp \
    settings.cpp \
    sidepanel.cpp \
    spinboxaction.cpp \
    statusbar.cpp \
    undostack.cpp \
    viewtoolbar.cpp

HEADERS  += \
    abstractdraw.h \
    asyncprocess.h \
    binaringfilterdialog.h \
    coloraction.h \
    colorbutton.h \
    currentsearchdialog.h \
    graph.h \
    graphicsview.h \
    graphv2.h \
    histogram.h \
    imageslider.h \
    mainwindow.h \
    menu.h \
    multidraw.h \
    newimage.h \
    paintdraw.h \
    preferences.h \
    settings.h \
    sidepanel.h \
    spinboxaction.h \
    statusbar.h \
    undostack.h \
    viewtoolbar.h

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../pid_lib/release/ -lpid_lib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../pid_lib/debug/ -lpid_lib
else:unix: LIBS += -L$$OUT_PWD/../pid_lib/ -lpid_lib

INCLUDEPATH += $$PWD/../pid_lib
DEPENDPATH += $$PWD/../pid_lib

RESOURCES += \
    ../res.qrc
