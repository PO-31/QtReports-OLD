TARGET = qtreports.so
QT += core widgets sql printsupport gui
CONFIG += release c++11
HEADERS += ./engine.hpp \
    ./translator.hpp
SOURCES += ./main.cpp \
    ./engine.cpp \
    ./translator.cpp
QMAKE_CXXFLAGS += -std=c++11