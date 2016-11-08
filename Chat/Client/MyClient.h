#pragma once
#include "Client.h"
#include <QMap>

namespace qRpc
{
    class ServerEmulated;
}

class Message;
class MyClient : public qRpc::Client
{
    Q_OBJECT

public:
    explicit MyClient(QObject* parent);

    void ConnectToServer(const QString& host, int port);

signals:
    void SendToServer(int id, const QTime& time, const QString& msg);
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
    qRpc::ServerEmulated* m_serverEmulated;
    int m_id;
    std::vector<Message> m_history;
};
