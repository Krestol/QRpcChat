#include "stdafx.h"
#include "Server.h"
#include "ClientEmulated.h"

qRpc::Server::Server()
    : m_clientEmulated(nullptr)
{
}

qRpc::ClientEmulated* qRpc::Server::GetClientEmulated(int port, QObject* realServer)
{
    m_clientEmulated = new qRpc::ClientEmulated(port, realServer, realServer);
    return m_clientEmulated;
}
