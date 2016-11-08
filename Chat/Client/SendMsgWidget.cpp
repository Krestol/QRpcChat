#include "stdafx.h"
#include "SendMsgWidget.h"
#include "ui_SendMsgWidget.h"

SendMsgWidget::SendMsgWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SendMsgWidget)
{
    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::clicked, this, &SendMsgWidget::OnSendMsg);
}

SendMsgWidget::~SendMsgWidget()
{
    delete ui;
}

void SendMsgWidget::OnSendMsg()
{
    emit SendMsg(ui->lineEdit->text());
    ui->lineEdit->clear();
}
