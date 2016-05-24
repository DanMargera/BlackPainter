#-------------------------------------------------
#
# Project created by QtCreator 2016-03-30T23:09:46
#
#-------------------------------------------------

TARGET = pid_lib
TEMPLATE = lib

DEFINES += PID_LIB_LIBRARY

SOURCES += \
    metadata.cpp \
    metadatafile.cpp \
    pidtools.cpp

HEADERS += \
    metadata.h \
    metadatafile.h \
    multi_vector.h \
    pidtools.h \
    complex.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
