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
	converters/convertertohtml.cpp \
	converters/convertertoqwidget.cpp \
	converters/convertertopdf.cpp \
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
    objectsplant.hpp \
	converters/convertertohtml.hpp \
	converters/convertertoqwidget.hpp \
	converters/convertertopdf.hpp \
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

coverage {
	QMAKE_CXXFLAGS += -g -Wall -fprofile-arcs -ftest-coverage -O0
	QMAKE_LDFLAGS += -g -Wall -fprofile-arcs -ftest-coverage  -O0
	QMAKE_CLEAN += $$OBJECTS_DIR/*.gcda $$OBJECTS_DIR/*.gcno
	LIBS += -lgcov

    zerocounters.commands = @lcov --directory \$(OBJECTS_DIR) --zerocounters
    QMAKE_EXTRA_TARGETS += zerocounters
    
    #echo "usage: ${0} <gcov-files-dir> \"<file-pattern>\" <target-dir>"
    #lcov -d ${1} -c -o ${1}/coverage.info
    #lcov --list-full-path -e ${1}/coverage.info ${2} -o ${1}/coverage-stripped.info
    #genhtml -o ${3} ${1}/coverage-stripped.info
    #lcov -d ${1} -z
    
    #../../coverage/
    capture.file = qtreportslib.cov
    #capture.commands = @mkdir -p ../../coverage && 
    capture.commands = lcov --base-directory $$_PRO_FILE_PWD_ --directory \$(OBJECTS_DIR) --capture --output-file $$capture.file
    capture.filters = \"/usr/*\" \"moc_*.cpp\" \"*3rdparty/*\" \"*QtCore/*\" \"*QtNetwork/*\" \"*corelib/*\" \"*network/*\"
    #!isEqual(IRC_MODULE, "IrcCore"):capture.filters += \"*/IrcCore/*\"
    #!isEqual(IRC_MODULE, "IrcModel"):capture.filters += \"*/IrcModel/*\"
    capture.commands += && lcov --remove $$capture.file $$capture.filters --output-file $$capture.file
    QMAKE_EXTRA_TARGETS += capture

    coverage.depends += zerocounters capture
    QMAKE_EXTRA_TARGETS += coverage
    message(Code coverage collection enabled)
}

message("Using spec: $$QMAKESPEC")
message("Compiler: $$QMAKE_CXX")