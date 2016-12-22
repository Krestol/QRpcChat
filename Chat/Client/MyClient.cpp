#include "stdafx.h"
#include "MyClient.h"
#include "ServerEmulated.h"
#include "Message.h"
#include "SerializeUtils.h"

MyClient::MyClient(QObject* parent)
    : ClientBase(parent)
    , m_remoteServer(nullptr)
{
}

void MyClient::ConnectToServer(const QString& host, int port)
{
    m_remoteServer = GetRemoteServer(port, host, this);
    connect(this, SIGNAL(NewMessage(int, const QTime&, const QString&)), m_remoteServer, SLOT(OnNewMsg(int, const QTime&, const QString&)));
    connect(this, SIGNAL(Registrate(const QString&)), m_remoteServer, SLOT(OnRegistration(const QString&)));
    connect(m_remoteServer, SIGNAL(OnRegistration_response(QString)), this, SLOT(OnRegistrationResponse(int, const QString&)));
    connect(this, SIGNAL(Update()), m_remoteServer, SLOT(OnUpdate()));
    connect(m_remoteServer, SIGNAL(OnUpdate_response()), this, SLOT(OnReceivedMsgHistory(QByteArray)));
}


void MyClient::OnSendMsg(const QString& msg)
{
    QTime time(QTime::currentTime());
    emit NewMessage(m_id, time, msg);
}

void MyClient::OnRegistrationResponse(int id, const QString& name)
{
    if (id != 0 && id != -1)
    {
        m_id = id;
        emit RegistrationSuccessful(id, name);
    }
    else
    {
        emit RegistrationFailed();
    }
}

void MyClient::OnReceivedMsgHistory(QByteArray history)
{
    m_history.clear();
    qRpc::DesrializeContainer<Message>(m_history, history);
    UpdateHistory(m_history);
}

void MyClient::OnUpdateHistory()
{
    emit Update();
}
