! include( ../common.pri ) {
    error( Couldnt find the common.pri file! )
}
QT       += core gui widgets

CONFIG += c++11

TARGET = BlackPainter

SOURCES += main.cpp\
        mainwindow.cpp \
    	graphicsview.cpp \
   	multidraw.cpp \
    	coloraction.cpp \
    	undostack.cpp \
    	paintdraw.cpp \
    	sidepanel.cpp \
    	histogram.cpp \
    	newimage.cpp \
    	colorbutton.cpp \
    	statusbar.cpp \
    	imageslider.cpp \
    	settings.cpp \
    	preferences.cpp \
    	spinboxaction.cpp \
    	graph.cpp \
    	graphv2.cpp \
    	currentsearchdialog.cpp \
    	asyncprocess.cpp

HEADERS  += mainwindow.h \
    	graphicsview.h \
    	abstractdraw.h \
    	multidraw.h \
    	coloraction.h \
    	undostack.h \
    	paintdraw.h \
    	sidepanel.h \
    	histogram.h \
    	newimage.h \
    	colorbutton.h \
    	statusbar.h \
    	imageslider.h \
    	settings.h \
    	preferences.h \
    	spinboxaction.h \
    	graph.h \
    	graphv2.h \
    	currentsearchdialog.h \
    	asyncprocess.h

INCLUDEPATH += ../pid_lib

LIBS += -L../pid_lib -lpid_lib

RESOURCES += \
    	../res.qrc
