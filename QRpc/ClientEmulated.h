#pragma once
#include <QObject>
#include "Utils.h"

class QTcpServer;
class QTcpSocket;
namespace qRpc
{
    class ClientEmulated : public QObject
    {
        Q_OBJECT

    public:
        ClientEmulated(int port, QObject* realServer, QObject* parent);
        void ExecuteSlot(QDataStream& in);

        template<typename... Targs>
        void EmitToRealClient(Targs... args)
        {
            utils::WriteToSocket(m_currentSlotToCall, m_currentOpenClientSocket, args...);
        }

    signals:
        void NewConnection();

    private slots:
        void OnNewConnection();
        void OnReadClient();

    private:
        QTcpServer* m_ptcpServer;
        quint16 m_nNextBlockSize;
        QObject* m_realServer;
        QTcpSocket* m_currentOpenClientSocket;
        QString m_currentSlotToCall;
    };
}

