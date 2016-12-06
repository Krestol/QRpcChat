#include "stdafx.h"
#include "ServerBase.h"
#include "ClientEmulated.h"

qRpc::ServerBase::ServerBase()
    : m_remoteClient(nullptr)
{
}

void qRpc::ServerBase::Listen(int port, QObject* realServer)
{
    m_remoteClient = new qRpc::ClientEmulated(port, realServer, realServer);
}
