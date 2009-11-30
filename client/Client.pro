# -------------------------------------------------
# Project created by QtCreator 2009-11-02T18:40:36
# -------------------------------------------------
QT += network
TARGET = Client
TEMPLATE = app
SOURCES += main.cpp \
    clientwindow.cpp \
    VLCWidget.cpp \
    menuwidget.cpp
HEADERS += clientwindow.h \
    VLCWidget.h \
    menuwidget.h
FORMS += 
LIBS += -LE:\Documents\Kurssit\MMJ\Qt_client\Client
LIBS += -lvlc
