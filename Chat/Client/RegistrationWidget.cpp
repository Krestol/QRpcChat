#include "RegistrationWidget.h"
#include "ui_RegistrationWidget.h"

RegistrationWidget::RegistrationWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegistrationWidget)
{
    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::clicked, this, &RegistrationWidget::OnRegistration);
    ui->alreadyExistLbl->hide();
}

RegistrationWidget::~RegistrationWidget()
{
    delete ui;
}

void RegistrationWidget::OnRegistration()
{
    emit Registration(ui->lineEdit->text());
    ui->lineEdit->clear();
}

void RegistrationWidget::WaitWhileRegistrate()
{
    ui->pushButton->setEnabled(false);
}

void RegistrationWidget::AskForAnotherName()
{
    ui->pushButton->setEnabled(true);
    ui->alreadyExistLbl->show();
}
