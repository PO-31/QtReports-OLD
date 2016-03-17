QT += core gui sql widgets printsupport

TARGET = qtreportslib
TEMPLATE = lib
CONFIG += c++11
DEFINES += QTREPORTS_LIBRARY

SOURCES += engine.cpp \
    processeddb.cpp \
    painter.cpp \
    parser.cpp \
    objectsplant.cpp \
	converters/convertertohtml.cpp \
	converters/convertertoqwidget.cpp \
	converters/convertertopdf.cpp \
    tags/object.cpp \
	tags/widget.cpp \
	tags/section.cpp \
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
    objectsplant.hpp \
	converters/convertertohtml.hpp \
	converters/convertertoqwidget.hpp \
	converters/convertertopdf.hpp \
	tags/object.hpp \
	tags/widget.hpp \
	tags/section.hpp \
    tags/report.hpp \
    tags/style.hpp \
	tags/field.hpp \
    tags/title.hpp \
    tags/detail.hpp \
    tags/band.hpp \
    tags/statictext.hpp \
	tags/textfield.hpp
	
QMAKE_CXXFLAGS += -std=c++11

unix {
    target.path = /usr/lib
    INSTALLS += target
    headers.files = $$HEADERS
    headers.path = /usr/include/qtreports/
    INSTALLS += headers
}

linux-clang {
    QMAKE_CXXFLAGS += -Wdocumentation
}

coverage {
    QMAKE_CXXFLAGS_RELEASE -= -O2
	QMAKE_CLEAN += $$OBJECTS_DIR/*.gcda $$OBJECTS_DIR/*.gcno
	QMAKE_CXXFLAGS += -c -g -Wall -fprofile-arcs -ftest-coverage -O0
	LIBS += -lgcov

    message(Code coverage collection enabled)
}
QMAKE_EXTRA_TARGETS += coverage

message("Using spec: $$QMAKESPEC")
message("Compiler: $$QMAKE_CXX")