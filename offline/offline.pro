! include( ../common.pri ) {
    error( Couldnt find the common.pri file! )
}
QT       += core gui

CONFIG += c++11

TARGET = offline

SOURCES += main.cpp

INCLUDEPATH += ../pid_lib

LIBS += -L../pid_lib -lpid_lib
