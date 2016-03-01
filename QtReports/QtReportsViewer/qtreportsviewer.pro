QT       +=  core gui sql widgets printsupport

TARGET = qtreportsviewer
TEMPLATE = app
CONFIG += release c++11

SOURCES += main.cpp \
            ../QtReports/engine.cpp \
            ../QtReports/parser.cpp \
            ../QtReports/processeddb.cpp \
            ../QtReports/painter.cpp \
            ../QtReports/objectsplant.cpp \
            ../QtReports/tags/object.cpp \
            ../QtReports/tags/report.cpp \
            ../QtReports/tags/style.cpp \
            ../QtReports/tags/title.cpp \
            ../QtReports/tags/statictext.cpp \
            ../QtReports/tags/detail.cpp \
            ../QtReports/tags/band.cpp \



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
