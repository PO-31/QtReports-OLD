QT       +=  core gui sql widgets printsupport

TARGET = qtreportsviewer
TEMPLATE = app
CONFIG += release c++11
INCLUDEPATH += ../qtreportslib
LIBPATH     += ../qtreportslib
LIBS   += -lqtreportslib

SOURCES += main.cpp
HEADERS += 

QMAKE_CXXFLAGS += -std=c++11

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
