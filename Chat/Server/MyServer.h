#pragma once
#include "ServerBase.h"
#include <QObject>
#include <QMap>
#include <QTime>

namespace qRpc
{
    class ClientEmulated;
}

class Message;
class MyServer : public QObject, private qRpc::ServerBase
{
    Q_OBJECT

public:
    explicit MyServer(QObject* parent);

public slots:
    void OnNewMsg(int id, const QTime& time, const QString& msg);
    void OnRegistration(const QString& name);
    void OnUpdate();

signals:
    void NewMsg(const QString& name, const QTime& time, const QString& msg);

private:
    qRpc::ClientEmulated* m_remoteClient;
    QMap<int, QString> m_users;
    QMap<QString, int> m_registrationMap;
    int m_lastId;
    QList<Message> m_messages;
};
