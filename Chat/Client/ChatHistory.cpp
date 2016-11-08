#include "ChatHistory.h"
#include "ui_ChatHistory.h"
#include "Message.h"

ChatHistory::ChatHistory(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatHistory)
{
    ui->setupUi(this);
}

ChatHistory::~ChatHistory()
{
    delete ui;
}

void ChatHistory::SetHistory(const std::vector<Message>& history)
{
    QString messages;
    for (const Message& msg : history)
    {
        messages.append(QString("[%0] [%1] %2\n").arg(msg.sendTime.toString(), msg.senderName, msg.text));
    }
    ui->label->setText(messages);
}
