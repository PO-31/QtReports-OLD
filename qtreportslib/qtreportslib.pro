QT += core gui sql widgets printsupport

TEMPLATE = lib
CONFIG += build_all
CONFIG += staticlib

SOURCES += engine.cpp \
    parsers/parserfromxml.cpp \
    converters/utils/replacer.cpp \
    converters/convertertohtml.cpp \
    converters/convertertoqwidget.cpp \
    converters/convertertopdf.cpp \
    tags/object.cpp \
    tags/widget.cpp \
    tags/section.cpp \
    tags/report.cpp \
    tags/style.cpp \
    tags/field.cpp \
    tags/group.cpp \
    tags/title.cpp \
    tags/detail.cpp \
    tags/band.cpp \
    tags/textwidget.cpp \
    tags/statictext.cpp \
    tags/textfield.cpp \
    tags/line.cpp \
    tags/rect.cpp \
    tags/ellipse.cpp \
    tags/image.cpp

HEADERS += engine.hpp \
    parsers/parserfromxml.hpp \
    converters/utils/replacer.hpp \
    converters/convertertohtml.hpp \
    converters/convertertoqwidget.hpp \
    converters/convertertopdf.hpp \
    tags/object.hpp \
    tags/widget.hpp \
    tags/section.hpp \
    tags/report.hpp \
    tags/style.hpp \
    tags/field.hpp \
    tags/group.hpp \
    tags/title.hpp \
    tags/detail.hpp \
    tags/band.hpp \
    tags/textwidget.hpp \
    tags/statictext.hpp \
    tags/textfield.hpp \
    tags/line.hpp \
    tags/rect.hpp \
    tags/ellipse.hpp \
    tags/image.hpp
	
QMAKE_CXXFLAGS += -std=c++11

unix {
    target.path = /usr/lib
    INSTALLS += target
    headers.files = $$HEADERS
    headers.path = /usr/include/qtreports/
    INSTALLS += headers
}

win32 {
    DESTDIR = $$PWD/build/
    VERSION = 1.0.0
    TARGET = $$qtLibraryTarget(qtreportslib)
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
