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
    , m_ui(new Ui::MainWindow)
    , m_connectionWidget(nullptr)
    , m_client(nullptr)
    , m_waitingWidget(nullptr)
    , m_sendMsgWidget(nullptr)
    , m_registrationWidget(nullptr)
    , m_historyWidget(nullptr)
    , m_timer(nullptr)
{
    m_ui->setupUi(this);
    m_ui->lblId->hide();

    setWindowTitle("Client");

    m_client = new MyClient(this);

    m_connectionWidget = new ConnectionWidget(this);
    m_waitingWidget = new WaitingWidget(this);
    m_sendMsgWidget = new SendMsgWidget(this);
    m_registrationWidget = new RegistrationWidget(this);
    m_historyWidget = new ChatHistory(this);
    m_timer = new QTimer(this);
    m_timer->setInterval(1000);
    m_timer->start();

    m_ui->stackedWidget->addWidget(m_connectionWidget);
    m_ui->stackedWidget->addWidget(m_waitingWidget);
    m_ui->stackedWidget->addWidget(m_registrationWidget);

    QWidget* chatWidget = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(chatWidget);
    layout->addWidget(m_historyWidget);
    layout->addWidget(m_sendMsgWidget);
    chatWidget->setLayout(layout);
    m_ui->stackedWidget->addWidget(chatWidget);

    connect(m_connectionWidget, &ConnectionWidget::ConnectToServer, this, &MainWindow::OnConnectToServer);
    connect(m_client, &MyClient::Connected, this, &MainWindow::OnConnectedToServer);
    connect(m_waitingWidget, &WaitingWidget::ChangeServer, this, &MainWindow::OnChangeServer);
    connect(m_sendMsgWidget, &SendMsgWidget::SendMsg, m_client, &MyClient::OnSendMsg);
    connect(m_registrationWidget, &RegistrationWidget::Registration, this, &MainWindow::OnTryToRegistration);
    connect(m_client, &MyClient::RegistrationSuccessful, this, &MainWindow::OnSuccessfulRegistration);
    connect(m_client, &MyClient::RegistrationFailed, this, &MainWindow::OnRegistrationFailed);
    connect(m_client, &MyClient::UpdateHistory, m_historyWidget, &ChatHistory::SetHistory);
    connect(m_timer, &QTimer::timeout, m_client, &MyClient::OnUpdateHistory);

    m_ui->stackedWidget->setCurrentIndex(PageConnection);
}

MainWindow::~MainWindow()
{
}

void MainWindow::OnConnectToServer(const QString& ip)
{
    m_ui->stackedWidget->setCurrentIndex(PageWaiting);
    m_client->ConnectToServer(ip, 2323);
}

void MainWindow::OnConnectedToServer()
{
    m_ui->stackedWidget->setCurrentIndex(PageRegistration);
}

void MainWindow::OnChangeServer()
{
    m_ui->stackedWidget->setCurrentIndex(PageConnection);
}

void MainWindow::OnTryToRegistration(const QString& name)
{
    m_client->Registrate(name);
}

void MainWindow::OnSuccessfulRegistration(int id, const QString& name)
{
    m_ui->lblId->setText(QString("name: %0; id: %1").arg(name, QString::number(id)));
    m_ui->lblId->show();
    m_ui->stackedWidget->setCurrentIndex(PageSend);
}

void MainWindow::OnRegistrationFailed()
{
    m_registrationWidget->AskForAnotherName();
}
