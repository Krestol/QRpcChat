#include "stdafx.h"
#include "Clientbase.h"
#include "ServerEmulated.h"
#include "Utils.h"

qRpc::ClientBase::ClientBase(QObject* parent)
    :QObject(parent)
{
}

qRpc::ServerEmulated* qRpc::ClientBase::GetRemoteServer(int port, const QString& host, QObject* parent)
{
    return new qRpc::ServerEmulated(port, host, this, parent);
}

QMetaObject::Connection qRpc::ClientBase::connect(QObject* sender, const char* signal, QObject* receiver, const char* method, Qt::ConnectionType type/* = Qt::AutoConnection*/)
{
    ServerEmulated* serverReceiver = dynamic_cast<ServerEmulated*>(receiver);
    ServerEmulated* serverSender = dynamic_cast<ServerEmulated*>(sender);

    if(serverReceiver != nullptr && serverSender == nullptr)
    {
        QMetaObject::Connection connection;

        const QString normalizedSignal(utils::GetNormalizedSignature(signal));
        if (!serverReceiver->IsSignalConnected(normalizedSignal))
        {
            const int signIndx = sender->metaObject()->indexOfSignal(normalizedSignal.toStdString().data());
            connection = QMetaObject::connect(this, signIndx, serverReceiver, 0);
        }
        serverReceiver->AddConnection(normalizedSignal, utils::GetNormalizedSignature(method));
        return connection;
    }
    else if (serverSender != nullptr && serverReceiver == nullptr)
    {
        const QString normalizedSlot(utils::GetNormalizedSignature(method));
        const QString normalizedSignal(utils::GetNormalizedSignature(signal));
        serverSender->AddConnection(normalizedSignal, normalizedSlot, receiver);
        return QMetaObject::Connection();
    }
    else if (serverSender == nullptr && serverReceiver == nullptr)
    {
        //todo connect server signal to server slot
        return QMetaObject::Connection();
    }
    else
    {
        return QObject::connect(sender, signal, receiver, method, type);
    }
}

QMetaObject::Connection qRpc::ClientBase::connect(const QObject *sender, const char *signal, const char *method, Qt::ConnectionType type)
{
    return QObject::connect(sender, signal, method, type);
}

QMetaObject::Connection qRpc::ClientBase::connect(const QObject *sender, const QMetaMethod &signal,
                    const QObject *receiver, const QMetaMethod &method,
                    Qt::ConnectionType type/* = Qt::AutoConnection*/)
{
    return QObject::connect(sender, signal, receiver, method, type);
}

