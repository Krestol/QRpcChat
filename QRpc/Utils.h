#pragma once

class QTcpSocket;
namespace qRpc
{
    namespace utils
    {
        void WriteToStreamLikeQVariant(const char* type, int indx, void** argv, QDataStream& out);
        void ParseArgs(const QString& signature, std::vector<QString>& args);
        QString GetNormalizedSignature(const QString& signature);
        void CastToVoidStar(const std::vector<QVariant>& argv, std::vector<void*>& castToVoid); //del
        void ExecuteSlotBySignature(const QString& signature, QDataStream& inStream, std::vector<QVariant>& argv, QObject* receiver);

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

        template<typename... Targs>
        void WriteToSocket(const QString& slot, QTcpSocket* socket, Targs... data)
        {
            std::vector<QVariant> argv;
            ExpandArgs(argv, data...);
            QByteArray arrBlock;
            QDataStream outStream(&arrBlock, QIODevice::ReadWrite);
            outStream.setVersion(QDataStream::Qt_5_7);
            outStream << quint16(0);
            outStream << slot;

            for (auto& arg : argv)
            {
                outStream << arg;
            }

            outStream.device()->seek(0);
            outStream << quint16(arrBlock.size() - sizeof(quint16));
            outStream.device()->seek(0);
            socket->write(arrBlock);
        }
    }
}
