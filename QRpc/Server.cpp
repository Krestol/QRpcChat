#include "stdafx.h"
#include "Server.h"
#include "ClientEmulated.h"

qRpc::Server::Server()
    : m_clientEmulated(nullptr)
{
}

void qRpc::Server::SetClientEmulated(int port, QObject* realServer)
{
    m_clientEmulated = new qRpc::ClientEmulated(port, realServer, realServer);
}
