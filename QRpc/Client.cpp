#include "stdafx.h"
#include "Client.h"
#include "ServerEmulated.h"
#include "Utils.h"

qRpc::Client::Client(QObject* parent)
    :QObject(parent)
{
}

QMetaObject::Connection qRpc::Client::connect(QObject* sender, const char* signal, QObject* receiver, const char* method, Qt::ConnectionType type)
{
    ServerEmulated* serverReceiver = dynamic_cast<ServerEmulated*>(receiver);
    ServerEmulated* serverSender = dynamic_cast<ServerEmulated*>(sender);

    if(serverReceiver != nullptr && serverSender == nullptr)
    {
        QMetaObject::Connection connection;

        const QString normalazedSignal(utils::GetNormalizedSignature(signal));
        if (!serverReceiver->IsSignalConnected(normalazedSignal))
        {
            const int signIndx = sender->metaObject()->indexOfSignal(normalazedSignal.toStdString().data());
            connection = QMetaObject::connect(this, signIndx, serverReceiver, 0);
        }
        serverReceiver->AddConnection(normalazedSignal, utils::GetNormalizedSignature(method));
        return connection;
    }
    else if (serverSender != nullptr && serverReceiver == nullptr)
    {
        const QString normalazedSlot(utils::GetNormalizedSignature(method));
        const QString normalazedSignal(utils::GetNormalizedSignature(signal));
        serverSender->AddConnection(normalazedSignal, normalazedSlot, receiver);
        return QMetaObject::Connection();
    }
    else if (serverSender == nullptr && serverReceiver == nullptr)
    {
        //todo connect server signal to server slot
    }
    else
    {
        return QObject::connect(sender, signal, receiver, method, type);
    }
}

QMetaObject::Connection qRpc::Client::connect(const QObject *sender, const char *signal, const char *method, Qt::ConnectionType type)
{
    return connect(sender, signal, method, type);
}

QMetaObject::Connection qRpc::Client::connect(const QObject *sender, const QMetaMethod &signal,
                    const QObject *receiver, const QMetaMethod &method,
                    Qt::ConnectionType type/* = Qt::AutoConnection*/)
{
    return QObject::connect(sender, signal, receiver, method, type);
}

