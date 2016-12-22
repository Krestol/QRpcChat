#pragma once

class QTcpServer;
class QTcpSocket;
namespace qRpc
{
    class ClientEmulated : public QObject
    {
        Q_OBJECT
    friend class ServerBase;
    public:
        ClientEmulated(int port, QObject* realServer, QObject* parent);

    signals:
        void NewConnection();

    private slots:
        void OnNewConnection();
        void OnReadClient();

    private:
        void ExecuteSlot(QDataStream& in);

        template<typename... Targs>
        void EmitToRealClient(Targs... args)
        {
            if (!m_currentSlotToCall.isEmpty())
            {
                std::vector<QVariant> argv;
                ExpandArgs(argv, args...);
                QByteArray arrBlock;
                QDataStream outStream(&arrBlock, QIODevice::ReadWrite);
                outStream.setVersion(QDataStream::Qt_5_7);
                outStream << quint16(0);
                outStream << m_currentSlotToCall;

                for (auto& arg : argv)
                {
                    outStream << arg;
                }

                outStream.device()->seek(0);
                outStream << quint16(arrBlock.size() - sizeof(quint16));
                outStream.device()->seek(0);
                m_currentOpenClientSocket->write(arrBlock);
            }
        }

        template<typename Targ>
        void ExpandArgs(std::vector<QVariant>& argv, Targ arg)
        {
             argv.push_back(QVariant(arg));
        }

        template<typename Targ, typename... Targs>
        void ExpandArgs(std::vector<QVariant>& argv, Targ arg, Targs... data)
        {
            ExpandArgs(argv, arg);
            ExpandArgs(argv, data...);
        }

    private:
        QTcpServer* m_ptcpServer;
        quint16 m_nNextBlockSize;
        QObject* m_realServer;
        QTcpSocket* m_currentOpenClientSocket;
        QString m_currentSlotToCall;
    };
}

