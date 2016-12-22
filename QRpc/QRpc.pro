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

PRECOMPILED_HEADER = stable.h

SOURCES += \
    ServerEmulated.cpp \
    ClientEmulated.cpp \
    ClientBase.cpp \
    Utils.cpp \
    ServerBase.cpp \
    SerializeUtils.cpp

HEADERS += \
    ServerEmulated.h \
    ClientEmulated.h \
    ClientBase.h \
    stdafx.h \
    Utils.h \
    ServerBase.h \
    SerializeUtils.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
