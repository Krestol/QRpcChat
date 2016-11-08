#-------------------------------------------------
#
# Project created by QtCreator 2016-11-07T19:21:52
#
#-------------------------------------------------
include(../QRpc.pri)

QT       -= gui

TARGET = ChatCommon
TEMPLATE = lib
CONFIG += staticlib
DESTDIR = $$LIBDIR

SOURCES += \
    Message.cpp

HEADERS += \
    stdafx.h \
    Message.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}

