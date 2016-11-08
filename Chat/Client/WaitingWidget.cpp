#include "stdafx.h"
#include "WaitingWidget.h"
#include "ui_WaitingWidget.h"

WaitingWidget::WaitingWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WaitingWidget)
{
    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::clicked, this, &WaitingWidget::ChangeServer);
}

WaitingWidget::~WaitingWidget()
{
    delete ui;
}

void WaitingWidget::Show(const QString& ip)
{
    ui->label->setText(QString("Waiting for connection to %0...").arg(ip));
}
