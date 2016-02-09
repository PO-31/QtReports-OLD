TEMPLATE = app
TARGET = QtReports
DESTDIR = ../Win32/Release
QT += core widgets gui
CONFIG += release
DEFINES += QT_DLL QT_WIDGETS_LIB
INCLUDEPATH += ./GeneratedFiles \
    . \
    ./GeneratedFiles/Release
DEPENDPATH += .
MOC_DIR += ./GeneratedFiles/release
OBJECTS_DIR += release
UI_DIR += ./GeneratedFiles
RCC_DIR += ./GeneratedFiles
HEADERS += ./qtreports.h
SOURCES += ./main.cpp \
    ./qtreports.cpp
FORMS += ./qtreports.ui
RESOURCES += qtreports.qrc
