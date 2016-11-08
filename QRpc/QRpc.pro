#-------------------------------------------------
#
# Project created by QtCreator 2016-10-30T13:31:48
#
#-------------------------------------------------
include(../QRpc.pri)

QT       -= gui
QT += core network widgets

DESTDIR = $$LIBDIR
TARGET = QRpc
TEMPLATE = lib
CONFIG += staticlib

SOURCES += qrpc.cpp \
    ServerEmulated.cpp \
    ClientEmulated.cpp \
    Client.cpp \
    Utils.cpp \
    Server.cpp

HEADERS += qrpc.h \
    ServerEmulated.h \
    ClientEmulated.h \
    Client.h \
    stdafx.h \
    Utils.h \
    Server.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
