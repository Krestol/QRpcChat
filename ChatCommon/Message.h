#pragma once
#include <QTime>

class Message
{
public:
    Message();
    Message(const QString& sender, const QTime& time, const QString& msg);

    friend QDataStream& operator << (QDataStream& stream, Message& message);
    friend QDataStream& operator >> (QDataStream& stream, Message& message);

    QString senderName;
    QTime sendTime;
    QString text;

};

QDataStream& operator << (QDataStream& stream, Message& message);
QDataStream& operator >> (QDataStream& stream, Message& message);
