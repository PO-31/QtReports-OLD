QT += core gui sql widgets printsupport

TARGET = qtreportslib
TEMPLATE = lib
CONFIG += release c++11
DEFINES += QTREPORTS_LIBRARY

SOURCES += engine.cpp \
    processeddb.cpp \
    painter.cpp \
    parser.cpp \
	converter.cpp \
    objectsplant.cpp \
    tags/object.cpp \
	tags/widget.cpp \
    tags/report.cpp \
    tags/style.cpp \
	tags/field.cpp \
    tags/title.cpp \
    tags/detail.cpp \
    tags/band.cpp \
    tags/statictext.cpp \
	tags/textfield.cpp

HEADERS += engine.hpp \
    processeddb.hpp \
    painter.hpp \
    parser.hpp \
	converter.hpp \
    objectsplant.hpp \
	tags/object.hpp \
	tags/widget.hpp \
    tags/report.hpp \
    tags/style.hpp \
	tags/field.hpp \
    tags/title.hpp \
    tags/detail.hpp \
    tags/band.hpp \
    tags/statictext.hpp \
	tags/textfield.hpp
	
# -g -Wall -fprofile-arcs -ftest-coverage -O0
QMAKE_CXXFLAGS += -std=c++11
#LIBS += -lgcov

unix {
    target.path = /usr/lib
    INSTALLS += target
    headers.files = $$HEADERS
    headers.path = /usr/include/qtreports/
    INSTALLS += headers
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