#include "stdafx.h"
#include "Server.h"
#include "ClientEmulated.h"

qRpc::Server::Server()
    : m_remoteClient(nullptr)
{
}

void qRpc::Server::Listen(int port, QObject* realServer)
{
    m_remoteClient = new qRpc::ClientEmulated(port, realServer, realServer);
}
