#include "stdafx.h"
#include "ClientEmulated.h"
#include "Utils.h"

qRpc::ClientEmulated::ClientEmulated(int port, QObject* realServer, QObject* parent)
    : QObject(parent)
    , m_realServer(realServer)
    , m_nNextBlockSize(0)
    , m_ptcpServer(new QTcpServer(this))
{
    if (!m_ptcpServer->listen(QHostAddress::Any, port))
    {
        QMessageBox::critical(0, "Server Error", "Unable to start server:" + m_ptcpServer->errorString());
        m_ptcpServer->close();
        return;
    }
    connect(m_ptcpServer, &QTcpServer::newConnection, this, &ClientEmulated::OnNewConnection);
    connect(m_ptcpServer, &QTcpServer::newConnection, this, &ClientEmulated::NewConnection);
}

void qRpc::ClientEmulated::OnNewConnection()
{
    QTcpSocket* clientSocket = m_ptcpServer->nextPendingConnection();
    connect(clientSocket, &QTcpSocket::disconnected, clientSocket, &QTcpSocket::deleteLater);
    connect(clientSocket, &QTcpSocket::readyRead, this, &ClientEmulated::OnReadClient);
}

void qRpc::ClientEmulated::ExecuteSlot(QDataStream& in)
{
    QStringList slotsToCall;
    in >> slotsToCall;
    m_currentSlotToCall.clear();
    for (auto& slot : slotsToCall)
    {
        m_currentSlotToCall = slot;
        std::vector<QVariant> argv;
        utils::ExecuteSlotBySignature(m_currentSlotToCall, in, argv, m_realServer);
        m_currentSlotToCall.clear();
    }
}

void qRpc::ClientEmulated::OnReadClient()
{
    m_currentOpenClientSocket = dynamic_cast<QTcpSocket*>(sender());
    QDataStream inStream(m_currentOpenClientSocket);
    inStream.setVersion(QDataStream::Qt_5_7);

    bool allDataReceived = false;
    while (!allDataReceived)
    {
        if (!m_nNextBlockSize)
        {
            if (m_currentOpenClientSocket->bytesAvailable() < sizeof(quint16))
            {
                break;
            }
            inStream >> m_nNextBlockSize;
        }

        int size = m_currentOpenClientSocket->bytesAvailable();
        if (size == m_nNextBlockSize)
        {
            m_nNextBlockSize = 0;
            allDataReceived = true;
        }
    }

    ExecuteSlot(inStream);
}
