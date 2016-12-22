#pragma once

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
        QString slotSignature;
    };

    class ClientBase;
    class ServerEmulated : public QObject
    {
    friend class ClientBase;
    public:
        ServerEmulated(int port, const QString& host, ClientBase* client, QObject* parent);
        int qt_metacall(QMetaObject::Call call, int id, void** argv);
        bool IsSignalConnected(const QString& signal);

    private slots:
        void OnResponse();

    private:
        void AddConnection(const QString& signal, const QString& slot);
        void AddConnection(const QString& signal, const QString& slot, QObject* receiver);
        void CallRealServer(void** argv);
        void EmitUnivesalSignal(QDataStream& data);

    private:
        const int m_port;
        QMap<QString, QString> m_serverSlots;
        QMap<QString, SlotToCall> m_clientSlots;
        QTcpSocket* m_tcpSocket;
        ClientBase* m_client;
        quint16 m_nNextBlockSize;

    };
}
