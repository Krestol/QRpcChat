#pragma once

namespace qRpc
{
    template<typename T>
    void ConvertToByteArray(T param, QByteArray& serialized)
    {
        QDataStream outStream(&serialized, QIODevice::WriteOnly);
        outStream.setVersion(QDataStream::Qt_5_7);
        outStream << param;
    }

    template<typename T>
    void ConvertFromByteArray(T& param, QByteArray& serialized)
    {
        QDataStream inStream(&serialized, QIODevice::ReadOnly);
        inStream.setVersion(QDataStream::Qt_5_7);
        inStream >> param;
    }

    template<typename TContainer>
    void SerializeContainer(TContainer& container, QByteArray& serialized)
    {
        QDataStream outStream(&serialized, QIODevice::WriteOnly);
        outStream.setVersion(QDataStream::Qt_5_7);

        const int size = container.size();
        outStream << size;

        for (int i = 0; i < size; ++i)
        {
            outStream << container.at(i);
        }
    }

    template<typename T, typename TContainer>
    void DesrializeContainer(TContainer& container, QByteArray& serialized)
    {
        QDataStream inStream(&serialized, QIODevice::ReadOnly);
        inStream.setVersion(QDataStream::Qt_5_7);

        int size;
        inStream >> size;
        for (int i = 0; i < size; ++i)
        {
            T param;
            inStream >> param;
            container.push_back(param);
        }
    }
}
