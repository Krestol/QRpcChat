#include "stdafx.h"
#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "ConnectionWidget.h"
#include "MyClient.h"
#include "WaitingWidget.h"
#include "SendMsgWidget.h"
#include "RegistrationWidget.h"
#include "ChatHistory.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_connectionWidget(nullptr)
    , m_client(nullptr)
    , m_waitingWidget(nullptr)
    , m_sendMsgWidget(nullptr)
    , m_registrationWidget(nullptr)
    , m_historyWidget(nullptr)
    , m_timer(nullptr)
{
    ui->setupUi(this);
    ui->lblId->hide();

    m_client = new MyClient(this);

    m_connectionWidget = new ConnectionWidget(this);
    m_waitingWidget = new WaitingWidget(this);
    m_sendMsgWidget = new SendMsgWidget(this);
    m_registrationWidget = new RegistrationWidget(this);
    m_historyWidget = new ChatHistory(this);
    m_timer = new QTimer(this);
    m_timer->setInterval(1000);
    m_timer->start();

    ui->stackedWidget->addWidget(m_connectionWidget);
    ui->stackedWidget->addWidget(m_waitingWidget);
    ui->stackedWidget->addWidget(m_registrationWidget);

    QWidget* chatWidget = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(chatWidget);
    layout->addWidget(m_sendMsgWidget);
    layout->addWidget(m_historyWidget);
    chatWidget->setLayout(layout);
    ui->stackedWidget->addWidget(chatWidget);

    connect(m_connectionWidget, &ConnectionWidget::ConnectToServer, this, &MainWindow::OnConnectToServer);
    connect(m_client, &MyClient::Connected, this, &MainWindow::OnConnectedToServer);
    connect(m_waitingWidget, &WaitingWidget::ChangeServer, this, &MainWindow::OnChangeServer);
    connect(m_sendMsgWidget, &SendMsgWidget::SendMsg, m_client, &MyClient::OnSendMsg);
    connect(m_registrationWidget, &RegistrationWidget::Registration, this, &MainWindow::OnTryToRegistration);
    connect(m_client, &MyClient::RegistrationSuccessful, this, &MainWindow::OnSuccessfulRegistration);
    connect(m_client, &MyClient::RegistrationFailed, this, &MainWindow::OnRegistrationFailed);
    connect(m_client, &MyClient::UpdateHistory, m_historyWidget, &ChatHistory::SetHistory);
    connect(m_timer, &QTimer::timeout, m_client, &MyClient::OnUpdateHistory);

    ui->stackedWidget->setCurrentIndex(PageConnection);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::OnConnectToServer(const QString& ip)
{
    ui->stackedWidget->setCurrentIndex(PageWaiting);
    m_client->ConnectToServer(ip, 2323);
}

void MainWindow::OnConnectedToServer()
{
    ui->stackedWidget->setCurrentIndex(PageRegistration);
}

void MainWindow::OnChangeServer()
{
    ui->stackedWidget->setCurrentIndex(PageConnection);
}

void MainWindow::OnTryToRegistration(const QString& name)
{
    m_client->Registrate(name);
}

void MainWindow::OnSuccessfulRegistration(int id, const QString& name)
{
    ui->lblId->setText(QString("name: %0; id: %1").arg(name, QString::number(id)));
    ui->lblId->show();
    ui->stackedWidget->setCurrentIndex(PageSend);
}

void MainWindow::OnRegistrationFailed()
{
    m_registrationWidget->AskForAnotherName();
}
