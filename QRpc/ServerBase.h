#pragma once

class QObject;
namespace qRpc
{
    class ClientEmulated;
    class ServerBase
    {
    public:
        ServerBase();
        virtual ~ServerBase(){}

    protected:
        ClientEmulated* Listen(int port, QObject* realServer);
        template<typename... Targs>
        void EmitResponseSignal(ClientEmulated* client, Targs... args)
        {
            if (client != nullptr)
            {
                client->EmitToRealClient(args...);
            }
            else
            {
                assert(!"Real server must to call Listen before EmitUniversalSignal");
            }
        }
    };
}

