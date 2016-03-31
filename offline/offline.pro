QT += core gui

CONFIG += c++11

TARGET = offline
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    main.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../pid_lib/release/ -lpid_lib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../pid_lib/debug/ -lpid_lib
else:unix: LIBS += -L$$OUT_PWD/../pid_lib/ -lpid_lib

INCLUDEPATH += $$PWD/../pid_lib
DEPENDPATH += $$PWD/../pid_lib
