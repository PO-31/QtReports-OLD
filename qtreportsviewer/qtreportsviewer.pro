QT       +=  core gui sql widgets printsupport

TARGET = qtreportsviewer
TEMPLATE = app
CONFIG += release c++11
INCLUDEPATH += ../qtreportslib
LIBPATH     += ../qtreportslib/build/
LIBS   += -L../../qtreportslib
LIBS   += -lqtreportslib

SOURCES += main.cpp

QMAKE_CXXFLAGS += -std=c++11

message("Using spec: $$QMAKESPEC")
message("Compiler: $$QMAKE_CXX")
