#include "ChatHistory.h"
#include "ui_ChatHistory.h"
#include "Message.h"

ChatHistory::ChatHistory(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::ChatHistory)
{
    m_ui->setupUi(this);
}

ChatHistory::~ChatHistory()
{
}

void ChatHistory::SetHistory(const std::vector<Message>& history)
{
    QStringList messages;
    for (const Message& msg : history)
    {
        messages.append(QString("[%0] [%1] %2\n").arg(msg.sendTime.toString(), msg.senderName, msg.text));
    }
    m_ui->listWidget->clear();
    m_ui->listWidget->addItems(messages);
}
