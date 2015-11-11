#-------------------------------------------------
#
# Project created by QtCreator 2015-11-11T21:52:05
#
#-------------------------------------------------

QT       -= gui

TARGET = QtGPIO
TEMPLATE = lib
CONFIG += staticlib

SOURCES += qtgpio.cpp

HEADERS += qtgpio.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
