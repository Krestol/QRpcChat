#include "stdafx.h"
#include "ServerWidget.h"
#include "ui_ServerWidget.h"
#include "ClientEmulated.h"

ServerWidget::ServerWidget(QWidget *parent)
    : QWidget(parent)
    , m_ui(new Ui::ServerWidget)
{
    m_ui->setupUi(this);
}

ServerWidget::~ServerWidget()
{
}

void ServerWidget::OnNewMsg(const QString& name, const QTime& time, const QString& msg)
{
    m_ui->listWidget->addItem(QString("[%0] [%1] %2").arg(time.toString(), name, msg));
}
