#include "stdafx.h"
#include "SendMsgWidget.h"
#include "ui_SendMsgWidget.h"

SendMsgWidget::SendMsgWidget(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::SendMsgWidget)
{
    m_ui->setupUi(this);
    connect(m_ui->pushButton, &QPushButton::clicked, this, &SendMsgWidget::OnSendMsg);
}

SendMsgWidget::~SendMsgWidget()
{
}

void SendMsgWidget::OnSendMsg()
{
    emit SendMsg(m_ui->lineEdit->text());
    m_ui->lineEdit->clear();
}

void SendMsgWidget::keyPressEvent(QKeyEvent* event)
{
    if(event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
    {
        OnSendMsg();
    }
}
