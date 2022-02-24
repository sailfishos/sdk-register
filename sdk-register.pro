TEMPLATE = app
TARGET = sdk-register
INCLUDEPATH += . src
QT -= gui

# Input
HEADERS += src/ssuregclient.h
SOURCES += src/main.cpp src/ssuregclient.cpp
LIBS += -lssu

reg.files = sdk-register
reg.path = /usr/libexec/sdk-setup

INSTALLS +=  reg

