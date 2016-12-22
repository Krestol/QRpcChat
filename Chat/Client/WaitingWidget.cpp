#include "stdafx.h"
#include "WaitingWidget.h"
#include "ui_WaitingWidget.h"

WaitingWidget::WaitingWidget(QWidget *parent)
    : QWidget(parent)
    , m_ui(new Ui::WaitingWidget)
{
    m_ui->setupUi(this);
    connect(m_ui->pushButton, &QPushButton::clicked, this, &WaitingWidget::ChangeServer);
}

WaitingWidget::~WaitingWidget()
{
}

void WaitingWidget::Show(const QString& ip)
{
    m_ui->label->setText(QString("Waiting for connection to %0...").arg(ip));
}
