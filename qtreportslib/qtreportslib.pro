QT += core gui sql widgets printsupport

TARGET = qtreports.lib
TEMPLATE = lib
CONFIG += release c++11
DEFINES += QTREPORTS_LIBRARY

SOURCES += tags/object.cpp \
    processeddb.cpp \
    painter.cpp \
    engine.cpp \
    parser.cpp \
    tags/style.cpp \
    tags/title.cpp \
    tags/statictext.cpp \
    tags/report.cpp \
    tags/detail.cpp \
    tags/band.cpp \
    objectsplant.cpp

HEADERS += tags/object.hpp \
    processeddb.hpp \
    painter.hpp \
    parser.hpp \
    engine.hpp \
    tags/style.hpp \
    tags/title.hpp \
    tags/statictext.hpp \
    tags/report.hpp \
    tags/detail.hpp \
    tags/band.hpp \
    objectsplant.hpp
	
QMAKE_CXXFLAGS += -std=c++11

unix {
    target.path = /usr/lib
    INSTALLS += target
}

linux-g++ | linux-g++-64 | linux-g++-32 {
    QMAKE_CXX = g++-4.8
    QMAKE_CC = gcc-4.8
}

linux-clang {
    QMAKE_CXX = clang++
    QMAKE_CC = clang
}

message("Using spec: $$QMAKESPEC")
message("Compiler: $$QMAKE_CXX")
