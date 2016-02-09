TARGET = qtreports.so
QT += core widgets sql printsupport gui
CONFIG += release
HEADERS += ./engine.hpp \
    ./translator.hpp
SOURCES += ./main.cpp \
    ./engine.cpp \
    ./translator.cpp
