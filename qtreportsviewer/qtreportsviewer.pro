QT       +=  core gui sql widgets printsupport

TARGET = qtreportsviewer
TEMPLATE = app
CONFIG += release c++11
INCLUDEPATH += ../qtreportslib
LIBPATH     += ../qtreportslib
LIBS   += -lqtreportslib

SOURCES += main.cpp
HEADERS += 

linux-g++ | linux-g++-64 | linux-g++-32 {
    QMAKE_CXX = g++-4.8
    QMAKE_CC = gcc-4.8
}

QMAKE_CXXFLAGS += -std=c++11

message("Using spec: $$QMAKESPEC")
message("Compiler: $$QMAKE_CXX")
