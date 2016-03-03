QT += core gui sql widgets printsupport

TARGET = qtreportslib
TEMPLATE = lib
CONFIG += release c++11
DEFINES += QTREPORTS_LIBRARY

SOURCES += engine.cpp \
    processeddb.cpp \
    painter.cpp \
    parser.cpp \
    objectsplant.cpp \
    tags/object.cpp \
    tags/style.cpp \
    tags/title.cpp \
    tags/statictext.cpp \
    tags/report.cpp \
    tags/detail.cpp \
    tags/band.cpp

HEADERS += engine.hpp \
    processeddb.hpp \
    painter.hpp \
    parser.hpp \
    objectsplant.hpp \
	tags/object.hpp \
    tags/style.hpp \
    tags/title.hpp \
    tags/statictext.hpp \
    tags/report.hpp \
    tags/detail.hpp \
    tags/band.hpp
	
QMAKE_CXXFLAGS += -std=c++11

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

######################################################################
# make coverage (debug)
######################################################################
 
coverage.CONFIG += recursive
QMAKE_EXTRA_TARGETS += coverage
 
CONFIG(debug,debug|release) {
    QMAKE_EXTRA_TARGETS += cov_cxxflags cov_lflags
 
    cov_cxxflags.target  = coverage
    cov_cxxflags.depends = CXXFLAGS += -fprofile-arcs -ftest-coverage
 
    cov_lflags.target  = coverage
    cov_lflags.depends = LFLAGS += -fprofile-arcs -ftest-coverage
 
    coverage.commands = @echo "Built with coverage support..."
    build_pass|!debug_and_release:coverage.depends = all
 
    QMAKE_CLEAN += $(OBJECTS_DIR)/*.gcda $(OBJECTS_DIR)/*.gcno
}