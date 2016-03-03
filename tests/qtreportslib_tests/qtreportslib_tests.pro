QT       +=  core gui sql widgets printsupport testlib

TARGET = qtreportslib_tests
TEMPLATE = app
CONFIG += release c++11

SOURCES += main.cpp \
            test_engine.cpp \
            ../../qtreportslib/engine.cpp \
            ../../qtreportslib/parser.cpp \
            ../../qtreportslib/processeddb.cpp \
            ../../qtreportslib/painter.cpp \
            ../../qtreportslib/objectsplant.cpp \
            ../../qtreportslib/tags/object.cpp \
            ../../qtreportslib/tags/report.cpp \
            ../../qtreportslib/tags/style.cpp \
            ../../qtreportslib/tags/title.cpp \
            ../../qtreportslib/tags/statictext.cpp \
            ../../qtreportslib/tags/detail.cpp \
            ../../qtreportslib/tags/band.cpp \

HEADERS  += test_engine.hpp \
            ../../qtreportslib/engine.hpp \
            ../../qtreportslib/parser.hpp \
            ../../qtreportslib/processeddb.hpp \
            ../../qtreportslib/painter.hpp \
            ../../qtreportslib/objectsplant.hpp \
            ../../qtreportslib/tags/object.cpp \
            ../../qtreportslib/tags/report.hpp \
            ../../qtreportslib/tags/style.hpp \
            ../../qtreportslib/tags/title.hpp \
            ../../qtreportslib/tags/statictext.hpp \
            ../../qtreportslib/tags/detail.hpp \
            ../../qtreportslib/tags/band.hpp

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
