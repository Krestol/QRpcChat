#include "stdafx.h"
#include "RegistrationWidget.h"
#include "ui_RegistrationWidget.h"

RegistrationWidget::RegistrationWidget(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::RegistrationWidget)
{
    m_ui->setupUi(this);
    connect(m_ui->pushButton, &QPushButton::clicked, this, &RegistrationWidget::OnRegistration);
    m_ui->alreadyExistLbl->hide();
}

RegistrationWidget::~RegistrationWidget()
{
}

void RegistrationWidget::OnRegistration()
{
    emit Registration(m_ui->lineEdit->text());
    m_ui->lineEdit->clear();
}

void RegistrationWidget::WaitWhileRegistrate()
{
    m_ui->pushButton->setEnabled(false);
}

void RegistrationWidget::AskForAnotherName()
{
    m_ui->pushButton->setEnabled(true);
    m_ui->alreadyExistLbl->show();
}

void RegistrationWidget::keyPressEvent(QKeyEvent* event)
{
    if(event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
    {
        OnRegistration();
    }
}
