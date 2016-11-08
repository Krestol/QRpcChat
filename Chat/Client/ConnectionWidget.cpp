#include "stdafx.h"
#include "ConnectionWidget.h"
#include "ui_ConnectionWidget.h"

ConnectionWidget::ConnectionWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConnectionWidget)
{
    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::clicked, this, &ConnectionWidget::OnConnect);
}

ConnectionWidget::~ConnectionWidget()
{
    delete ui;
}

void ConnectionWidget::OnConnect()
{
    emit ConnectToServer(ui->lineEdit->text());
}
