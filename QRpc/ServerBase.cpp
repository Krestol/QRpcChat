#include "stdafx.h"
#include "ServerBase.h"
#include "ClientEmulated.h"

qRpc::ServerBase::ServerBase()
{
}

qRpc::ClientEmulated* qRpc::ServerBase::Listen(int port, QObject* realServer)
{
    return new qRpc::ClientEmulated(port, realServer, realServer);
}
