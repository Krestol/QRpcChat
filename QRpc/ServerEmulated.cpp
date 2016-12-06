#include "stdafx.h"
#include "ServerEmulated.h"
#include "Utils.h"
#include "ClientBase.h"

qRpc::ServerEmulated::ServerEmulated(int port, const QString& host, ClientBase* client, QObject* parent)
    : QObject(parent)
    , m_port(port)
    , m_nNextBlockSize(0)
    , m_client(client)
{
    m_tcpSocket = new QTcpSocket(this);
    m_tcpSocket->connectToHost(host, port);
    connect(m_tcpSocket, &QTcpSocket::readyRead, this, &ServerEmulated::OnResponse);
    connect(m_tcpSocket, &QTcpSocket::readyRead, this, &ServerEmulated::OnConnected);
}

void qRpc::ServerEmulated::AddConnection(const QString& signal, const QString& slot)
{
    m_serverSlots.insertMulti(signal, slot);
}

void qRpc::ServerEmulated::AddConnection(const QString& signal, const QString& slot, QObject* receiver)
{
    m_clientSlots.insertMulti(signal, SlotToCall(slot, receiver));
}

bool qRpc::ServerEmulated::IsSignalConnected(const QString& signal)
{
    return m_serverSlots.find(signal) != m_serverSlots.end();
}

void qRpc::ServerEmulated::CallRealServer(void** argv)
{
    QByteArray arrBlock;
    QDataStream outStream(&arrBlock, QIODevice::WriteOnly);
    outStream.setVersion(QDataStream::Qt_5_7);

    QMetaMethod metaMethod = sender()->metaObject()->method(senderSignalIndex());
    QString normalizedSignal(QMetaObject::normalizedSignature(metaMethod.methodSignature()));

    QStringList slotsToCall(m_serverSlots.values(normalizedSignal));
    if (!slotsToCall.empty())
    {
        outStream << quint16(0) << slotsToCall;

        std::vector<QString> args;
        utils::ParseArgs(normalizedSignal.toStdString().data(), args);

        int indx = 0;
        for (auto& arg : args)
        {
            ++indx;
            utils::WriteToStreamLikeQVariant(arg.toStdString().data(), indx, argv, outStream);
        }

        outStream.device()->seek(0);
        outStream << quint16(arrBlock.size() - sizeof(quint16));
        m_tcpSocket->write(arrBlock);
    }
}

int qRpc::ServerEmulated::qt_metacall(QMetaObject::Call /*call*/, int id, void** argv)
{
    CallRealServer(argv);
    return id;
}

void qRpc::ServerEmulated::OnResponse()
{
    QDataStream inStream(m_tcpSocket);
    inStream.setVersion(QDataStream::Qt_5_7);

    for (;;)
    {
        if (!m_nNextBlockSize)
        {
            if (m_tcpSocket->bytesAvailable() < sizeof(quint16))
            {
                break;
            }
            inStream >> m_nNextBlockSize;

            if (m_tcpSocket->bytesAvailable() < m_nNextBlockSize)
            {
                continue;
            }
        }
        else
        {
            m_nNextBlockSize = 0;
            break;
        }
    }

    EmitUnivesalSignal(inStream);
}
void qRpc::ServerEmulated::EmitUnivesalSignal(QDataStream& data)
{
    QString serverSignal;
    data >> serverSignal;
    serverSignal.insert(serverSignal.indexOf('('), "_signal");

    QList<SlotToCall> slotsToCall = m_clientSlots.values(serverSignal);

    for (auto& slot : slotsToCall)
    {
        std::vector<QVariant> argv;
        utils::ExecuteSlotBySignature(slot.slotSignature, data, argv, slot.object);
    }
}

void qRpc::ServerEmulated::OnConnected()
{
    m_client->Connected();
    disconnect(m_tcpSocket, &QTcpSocket::readyRead, this, &ServerEmulated::OnConnected);
}
