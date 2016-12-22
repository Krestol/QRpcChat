#-------------------------------------------------
#
# Project created by QtCreator 2016-10-30T16:41:25
#
#-------------------------------------------------
include(../../QRpc.pri)

QT += core network widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Client
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
        ConnectionWidget.cpp \
        MyClient.cpp \
        WaitingWidget.cpp \
        SendMsgWidget.cpp \
        RegistrationWidget.cpp \
        ChatHistory.cpp

HEADERS  += MainWindow.h \
        ConnectionWidget.h \
        stdafx.h \
        MyClient.h \
        WaitingWidget.h \
        SendMsgWidget.h \
        RegistrationWidget.h \
        ChatHistory.h

FORMS    += MainWindow.ui \
        ConnectionWidget.ui \
        WaitingWidget.ui \
        SendMsgWidget.ui \
        RegistrationWidget.ui \
        ChatHistory.ui
