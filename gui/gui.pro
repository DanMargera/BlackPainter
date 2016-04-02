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
    graphicsview.cpp \
    imageslider.cpp \
    main.cpp \
    mainwindow.cpp \
    multidraw.cpp \
    paintdraw.cpp \
    sidepanel.cpp \
    statusbar.cpp \
    undostack.cpp \
    viewtoolbar.cpp \
    filtercontroller.cpp \
    Dialog/brightnesscontrastfilterdialog.cpp \
    Dialog/currentsearchdialog.cpp \
    Dialog/levelsfilterdialog.cpp \
    Dialog/thresholdfilterdialog.cpp \
    Dialog/newimagedialog.cpp \
    Dialog/preferencesdialog.cpp \
    Graphs/graph.cpp \
    Graphs/graphv2.cpp \
    Graphs/histogram.cpp \
    Components/coloraction.cpp \
    Components/colorbutton.cpp \
    Components/spinboxaction.cpp


HEADERS  += \
    abstractdraw.h \
    asyncprocess.h \
    graphicsview.h \
    imageslider.h \
    mainwindow.h \
    multidraw.h \
    paintdraw.h \
    sidepanel.h \
    statusbar.h \
    undostack.h \
    viewtoolbar.h \
    filtercontroller.h \
    Dialog/brightnesscontrastfilterdialog.h \
    Dialog/currentsearchdialog.h \
    Dialog/levelsfilterdialog.h \
    Dialog/thresholdfilterdialog.h \
    Dialog/newimagedialog.h \
    Dialog/preferencesdialog.h \
    Graphs/graph.h \
    Graphs/graphv2.h \
    Graphs/histogram.h \
    Components/colorbutton.h \
    Components/spinboxaction.h \
    Components/coloraction.h


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../pid_lib/release/ -lpid_lib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../pid_lib/debug/ -lpid_lib
else:unix: LIBS += -L$$OUT_PWD/../pid_lib/ -lpid_lib

INCLUDEPATH += $$PWD/../pid_lib
DEPENDPATH += $$PWD/../pid_lib

RESOURCES += \
    ../res.qrc
