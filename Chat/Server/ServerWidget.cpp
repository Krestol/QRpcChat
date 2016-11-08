#include "stdafx.h"
#include "ServerWidget.h"
#include "ui_ServerWidget.h"
#include "ClientEmulated.h"

ServerWidget::ServerWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ServerWidget)
{
    ui->setupUi(this);
}

ServerWidget::~ServerWidget()
{
    delete ui;
}

void ServerWidget::OnNewMsg(const QString& name, const QTime& time, const QString& msg)
{
    ui->label->setText(ui->label->text() + "\n" + QString("[%0] [%1] %2").arg(time.toString(), name, msg));
}
