#include "stdafx.h"
#include "MyServer.h"
#include "ClientEmulated.h"
#include "Message.h"

MyServer::MyServer(QObject* parent)
    : QObject(parent)
    , m_lastId(0)
{
    SetClientEmulated(2323, this);
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
        EmitUniversalSignal(-1);
    }
    else
    {
        ++ m_lastId;
        m_registrationMap.insert(name, m_lastId);
        m_users.insert(m_lastId, name);
        EmitUniversalSignal(m_lastId, name);
    }
}

void MyServer::OnUpdate()
{
    QByteArray history;
    QDataStream outStream(&history, QIODevice::WriteOnly);
    outStream.setVersion(QDataStream::Qt_5_7);

    const int size = m_messages.size();
    outStream << size;

    for (int i = 0; i < size; ++i)
    {
        Message msg(m_messages.at(i));
        outStream << msg;
    }
    EmitUniversalSignal(history);
}
