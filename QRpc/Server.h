#pragma once
#include "ClientEmulated.h"

class QObject;
namespace qRpc
{
    class Server
    {
    public:
        Server();
        virtual ~Server(){}

    protected:
        void SetClientEmulated(int port, QObject* realServer);
        template<typename... Targs>
        void EmitUniversalSignal(Targs... args)
        {
            if (m_clientEmulated != nullptr)
            {
                m_clientEmulated->EmitToRealClient(args...);
            }
            else
            {
                assert(!"Real server must to call SetClientEmulated before EmitUniversalSignal");
            }
        }

    private:
        ClientEmulated* m_clientEmulated;
    };
}

