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
    }
}
