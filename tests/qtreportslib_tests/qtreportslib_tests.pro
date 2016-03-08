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

coverage {
	QMAKE_CXXFLAGS += -c -g -Wall -fprofile-arcs -ftest-coverage -O0
	QMAKE_LDFLAGS += -c -g -Wall -fprofile-arcs -ftest-coverage -O0
	LIBS += -lgcov

    zerocounters.commands = @lcov --directory \$(OBJECTS_DIR) --zerocounters
    QMAKE_EXTRA_TARGETS += zerocounters
    
    capture.file = qtreportslib_tests.cov
    capture.commands = lcov --base-directory $$_PRO_FILE_PWD_ --directory \$(OBJECTS_DIR) --capture --output-file $$capture.file
    capture.filters = \"/usr/*\" \"moc_*.cpp\" \"*3rdparty/*\" \"*QtCore/*\" \"*QtNetwork/*\" \"*corelib/*\" \"*network/*\"
    #!isEqual(IRC_MODULE, "IrcCore"):capture.filters += \"*/IrcCore/*\"
    #!isEqual(IRC_MODULE, "IrcModel"):capture.filters += \"*/IrcModel/*\"
    capture.commands += && lcov --remove $$capture.file $$capture.filters --output-file $$capture.file
    QMAKE_EXTRA_TARGETS += capture

    coverage.depends += capture zerocounters
    message(Code coverage collection enabled)
}
QMAKE_EXTRA_TARGETS += coverage

QMAKE_CXXFLAGS += -std=c++11

message("Using spec: $$QMAKESPEC")
message("Compiler: $$QMAKE_CXX")
