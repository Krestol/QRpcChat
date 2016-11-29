#include "stdafx.h"
#include "Message.h"

Message::Message()
{}

Message::Message(const QString& sender, const QTime& time, const QString& msg)
    : senderName(sender)
    , sendTime(time)
    , text(msg)
{}


QDataStream& operator << (QDataStream& stream, const Message& message)
{
    stream << message.senderName << message.sendTime << message.text;
    return stream;
}

QDataStream& operator >> (QDataStream& stream, Message& message)
{
    stream >> message.senderName >> message.sendTime >> message.text;
    return stream;
}
