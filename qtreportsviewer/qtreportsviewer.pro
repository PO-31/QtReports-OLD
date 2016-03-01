QT       +=  core gui sql widgets printsupport

TARGET = qtreportsviewer
TEMPLATE = app
CONFIG += release c++11

SOURCES += main.cpp \
            ../qtreportslib/engine.cpp \
            ../qtreportslib/parser.cpp \
            ../qtreportslib/processeddb.cpp \
            ../qtreportslib/painter.cpp \
            ../qtreportslib/objectsplant.cpp \
            ../qtreportslib/tags/object.cpp \
            ../qtreportslib/tags/report.cpp \
            ../qtreportslib/tags/style.cpp \
            ../qtreportslib/tags/title.cpp \
            ../qtreportslib/tags/statictext.cpp \
            ../qtreportslib/tags/detail.cpp \
            ../qtreportslib/tags/band.cpp \



HEADERS  += ../QtReports/engine.hpp \
            ../QtReports/parser.hpp \
            ../QtReports/processeddb.hpp \
            ../QtReports/painter.hpp \
            ../QtReports/objectsplant.hpp \
            ../QtReports/tags/object.cpp \
            ../QtReports/tags/report.hpp \
            ../QtReports/tags/style.hpp \
            ../QtReports/tags/title.hpp \
            ../QtReports/tags/statictext.hpp \
            ../QtReports/tags/detail.hpp \
            ../QtReports/tags/band.hpp

QMAKE_CXXFLAGS += -std=c++11
