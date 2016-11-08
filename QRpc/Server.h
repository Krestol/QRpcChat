#pragma once
#include "ClientEmulated.h"
class QObject;
namespace qRpc
{
    class Server
    {
    public:
        Server();

        ClientEmulated* GetClientEmulated(int port, QObject* realServer);

    protected:
        template<typename... Targs>
        void EmitUniversalSignal(Targs... args)
        {
            m_clientEmulated->EmitToRealClient(args...);
        }

    private:
        ClientEmulated* m_clientEmulated;
    };
}

