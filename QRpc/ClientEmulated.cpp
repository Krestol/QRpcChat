#include "stdafx.h"
#include "ClientEmulated.h"
#include "Utils.h"

namespace
{
    void SendToClient(const QString& str, QTcpSocket* socket)
    {
        QByteArray arrBlock;
        QDataStream outStream(&arrBlock, QIODevice::WriteOnly);
        outStream.setVersion(QDataStream::Qt_5_7);
        outStream << quint16(0) << str;

        outStream.device()->seek(0);
        outStream << quint16(arrBlock.size() - sizeof(quint16));
        socket->write(arrBlock);
    }
}
qRpc::ClientEmulated::ClientEmulated(int port, QObject* realServer, QObject* parent)
    : QObject(parent)
    , m_realServer(realServer)
{
    m_nNextBlockSize = 0;
    m_ptcpServer = new QTcpServer(this);
    if (!m_ptcpServer->listen(QHostAddress::Any, port))
    {
        QMessageBox::critical(0, "Server Error", "Unable to start server:" + m_ptcpServer->errorString());
        m_ptcpServer->close();
        return;
    }
    connect(m_ptcpServer, &QTcpServer::newConnection, this, &ClientEmulated::OnNewConnection);
}

void qRpc::ClientEmulated::OnNewConnection()
{
    emit NewConnection();
    QTcpSocket* clientSocket = m_ptcpServer->nextPendingConnection();
    connect(clientSocket, &QTcpSocket::disconnected, clientSocket, &QTcpSocket::deleteLater);
    connect(clientSocket, &QTcpSocket::readyRead, this, &ClientEmulated::OnReadClient);
    SendToClient("Connected", clientSocket);
}

void qRpc::ClientEmulated::ExecuteSlot(QDataStream& in)
{
    QStringList slotsToCall;
    in >> slotsToCall;
    for (auto& slot : slotsToCall)
    {
        m_currentSlotToCall = slot;
        std::vector<QVariant> argv;
        utils::ExecuteSlotBySignature(m_currentSlotToCall, in, argv, m_realServer);
    }
}

void qRpc::ClientEmulated::OnReadClient()
{
    m_currentOpenClientSocket = dynamic_cast<QTcpSocket*>(sender());
    QDataStream inStream(m_currentOpenClientSocket);
    inStream.setVersion(QDataStream::Qt_5_7);

    for (;;)
    {
        if (!m_nNextBlockSize)
        {
            if (m_currentOpenClientSocket->bytesAvailable() < sizeof(quint16))
            {
                break;
            }
            inStream >> m_nNextBlockSize;
        }

        if (m_currentOpenClientSocket->bytesAvailable() < m_nNextBlockSize)
        {
            break;
        }

        ExecuteSlot(inStream);

        m_nNextBlockSize = 0;
    }
}
