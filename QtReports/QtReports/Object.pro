#-------------------------------------------------
#
# Project created by QtCreator 2016-02-17T21:32:30
#
#-------------------------------------------------

QT       += core gui sql widgets printsupport

TARGET = Object
TEMPLATE = lib

DEFINES += OBJECT_LIBRARY

SOURCES += Object.cpp \
    ProcessedDB.cpp \
    Painter.cpp \
    Engine.cpp \
    Translator.cpp \
    Style.cpp \
    Title.cpp \
    StaticText.cpp \
    Report.cpp \
    Detail.cpp \
    Band.cpp \
    ObjectsPlant.cpp

HEADERS += Object.h \
    ProcessedDB.h \
    Painter.h \
    Translator.h \
    Engine.h \
    Style.h \
    Title.h \
    StaticText.h \
    Report.h \
    Detail.h \
    Band.h \
    ObjectsPlant.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
