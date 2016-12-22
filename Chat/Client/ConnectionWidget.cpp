#include "stdafx.h"
#include "ConnectionWidget.h"
#include "ui_ConnectionWidget.h"

ConnectionWidget::ConnectionWidget(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::ConnectionWidget)
{
    m_ui->setupUi(this);
    connect(m_ui->pushButton, &QPushButton::clicked, this, &ConnectionWidget::OnConnect);
}

ConnectionWidget::~ConnectionWidget()
{
}

void ConnectionWidget::OnConnect()
{
    emit ConnectToServer(m_ui->lineEdit->text());
}

void ConnectionWidget::keyPressEvent(QKeyEvent* event)
{
    if(event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
    {
        OnConnect();
    }
}
