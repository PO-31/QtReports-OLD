QT += core gui sql widgets printsupport

TARGET = qtreports.lib
TEMPLATE = lib
CONFIG += release c++11
DEFINES += QTREPORTS_LIBRARY

SOURCES += tags/object.cpp \
    processeddb.cpp \
    painter.cpp \
    engine.cpp \
    translator.cpp \
    tags/style.cpp \
    tags/title.cpp \
    tags/statictext.cpp \
    tags/report.cpp \
    tags/detail.cpp \
    tags/band.cpp \
    objectsplant.cpp

HEADERS += tags/object.h \
    processeddb.h \
    painter.h \
    translator.h \
    engine.h \
    tags/style.h \
    tags/title.h \
    tags/statictext.h \
    tags/report.h \
    tags/detail.h \
    tags/band.h \
    objectsplant.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

QMAKE_CXXFLAGS += -std=c++11
