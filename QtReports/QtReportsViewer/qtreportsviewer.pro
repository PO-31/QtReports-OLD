TARGET = QtReportsViewer
QT += core widgets gui
CONFIG += release
DEFINES += QT_DLL QT_WIDGETS_LIB
HEADERS += ./qtreportsviewer.h
SOURCES += ./main.cpp \
    ./qtreportsviewer.cpp
FORMS += ./qtreportsviewer.ui
RESOURCES += qtreportsviewer.qrc
