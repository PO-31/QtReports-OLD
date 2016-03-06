QT += core gui sql widgets printsupport testlib

TARGET = qtreportslib_tests
TEMPLATE = app
CONFIG += release c++11
INCLUDEPATH += ../../qtreportslib
LIBPATH     += ../../qtreportslib
LIBS   += -lqtreportslib

SOURCES += main.cpp \
           test_engine.cpp

HEADERS  += test_engine.hpp

QMAKE_CXXFLAGS += -std=c++11

message("Using spec: $$QMAKESPEC")
message("Compiler: $$QMAKE_CXX")
