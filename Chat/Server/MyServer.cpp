#include "stdafx.h"
#include "MyServer.h"
#include "ClientEmulated.h"
#include "Message.h"
#include "SerializeUtils.h"

MyServer::MyServer(QObject* parent)
    : QObject(parent)
    , m_lastId(0)
{
    m_client = Listen(2323, this);
}

void MyServer::OnNewMsg(int id, const QTime& time, const QString& msg)
{
    const QString sender(m_users.value(id));

    m_messages.append(Message(sender, time, msg));
    emit NewMsg(sender, time, msg);
}

void MyServer::OnRegistration(const QString& name)
{
    bool isTheSameNamePresent = (m_registrationMap.find(name) != m_registrationMap.end());
    if (isTheSameNamePresent)
    {
        EmitResponseSignal(m_client, -1);
    }
    else
    {
        ++ m_lastId;
        m_registrationMap.insert(name, m_lastId);
        m_users.insert(m_lastId, name);
        EmitResponseSignal(m_client, m_lastId, name);
    }
}

void MyServer::OnUpdate()
{
    QByteArray history;
    qRpc::SerializeContainer(m_messages, history);
    EmitResponseSignal(m_client, history);
}
