QT += core gui sql widgets printsupport testlib

TARGET = qtreportslib_tests
TEMPLATE = app
CONFIG += release c++11
INCLUDEPATH += ../../qtreportslib
win32: LIBS   += -L "$$PWD"/../../qtreportslib/build/
linux: LIBS   += -L "$$PWD"/../../qtreportslib/build/
LIBS   += -lqtreportslib
DESTDIR = $$PWD/build/

SOURCES += main.cpp \
    test_engine.cpp \
    test_parser.cpp \
    test_convertertoqwidget.cpp \
    test_convertertopdf.cpp \
    test_convertertohtml.cpp \
    test_groups.cpp \
    test_field.cpp

HEADERS  += test_engine.hpp \
    test_parser.hpp \
    test_convertertoqwidget.hpp \
    test_convertertopdf.hpp \
    test_convertertohtml.hpp \
    test_groups.hpp \
    test_field.hpp

QMAKE_CXXFLAGS += -std=c++11

message("Using spec: $$QMAKESPEC")
message("Compiler: $$QMAKE_CXX")

