#pragma once
#include "ClientBase.h"
#include <QMap>

namespace qRpc
{
    class ServerEmulated;
}

class Message;
class MyClient : public qRpc::ClientBase
{
    Q_OBJECT

public:
    explicit MyClient(QObject* parent);

    void ConnectToServer(const QString& host, int port);

signals:
    void NewMessage(int id, const QTime& time, const QString& msg);
    void Registrate(const QString&);
    void RegistrationSuccessful(int id, const QString& name);
    void RegistrationFailed();
    void UpdateHistory(const std::vector<Message>& history);
    void Update();

public slots:
    void OnSendMsg(const QString& msg);
    void OnUpdateHistory();

private slots:
    void OnRegistrationResponse(int id, const QString& name);
    void OnReceivedMsgHistory(QByteArray history);

private:
    qRpc::ServerEmulated* m_remoteServer;
    int m_id;
    std::vector<Message> m_history;
};
