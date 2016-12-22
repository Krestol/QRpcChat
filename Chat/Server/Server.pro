#-------------------------------------------------
#
# Project created by QtCreator 2016-10-30T14:26:15
#
#-------------------------------------------------
include(../../QRpc.pri)

QT       += core gui network widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Server
TEMPLATE = app

LIBS += -L$$LIBDIR

LIBS += -lqrpc -lChatCommon

PRECOMPILED_HEADER = stable.h

INCLUDEPATH += \
            . \
            .. \
            $${QRPC_INC} \
            $${CHAT_COMMON}

SOURCES += main.cpp\
        MainWindow.cpp \
        ServerWidget.cpp \
        MyServer.cpp

HEADERS += MainWindow.h \
        ServerWidget.h \
        stdafx.h \
        MyServer.h

FORMS   += MainWindow.ui \
        ServerWidget.ui
