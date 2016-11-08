#pragma once
#include <QMap>

class QTcpSocket;
namespace qRpc
{
    struct SlotToCall
    {
        SlotToCall()
            : object(nullptr)
        { }

        SlotToCall(const QString& signature, QObject* obj)
            : object(obj)
            , slotSignature(signature)
        { }

        QObject* object;
        const QString slotSignature;
    };

    class Client;
    class ServerEmulated : public QObject
    {
    public:
        ServerEmulated(int port, const QString& host, Client* client, QObject* parent);
        int qt_metacall(QMetaObject::Call call, int id, void** argv);
        void AddConnection(const QString& signal, const QString& slot);
        void AddConnection(const QString& signal, const QString& slot, QObject* receiver);
        bool IsSignalConnected(const QString& signal);

    private slots:
        void OnResponse();

    private:
        void CallRealServer(void** argv);
        void EmitUnivesalSignal(QDataStream& data);
        void OnConnected();

    private:
        const int m_port;
        QMap<QString, QString> m_serverSlots;
        QMap<QString, SlotToCall> m_clientSlots;
        QTcpSocket* m_tcpSocket;
        Client* m_client;
        quint16 m_nNextBlockSize;

    };
}
