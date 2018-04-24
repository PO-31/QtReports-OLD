QT += core gui sql widgets printsupport

TARGET = qtreportsviewer
TEMPLATE = app
CONFIG += release c++11
INCLUDEPATH += ../qtreportslib
win32: LIBS   += -L "$$PWD"/../qtreportslib/build/
unix: LIBS   += -L"$$PWD"/../qtreportslib/build/
LIBS   += -lqtreportslib
DESTDIR = $$PWD/build/

SOURCES += main.cpp

QMAKE_CXXFLAGS += -std=c++11

message("Using LIB: $$LIBS")
message("Using spec: $$QMAKESPEC")
message("Compiler: $$QMAKE_CXX")
