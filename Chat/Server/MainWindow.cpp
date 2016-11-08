#include "stdafx.h"
#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "ServerWidget.h"
#include "MyServer.h"

namespace
{
    QString GetIp()
    {
        const QString localhost = "127.0.0.1";
        QList<QNetworkInterface> interfaces = QNetworkInterface::allInterfaces();
        for (QNetworkInterface& h : interfaces)
        {
            QList<QNetworkAddressEntry> entries = h.addressEntries();
            for (QNetworkAddressEntry& entry : entries)
            {
                if(entry.ip().protocol() == QAbstractSocket::IPv4Protocol)
                {
                    QString ip(entry.ip().toString());
                    if  (entry.ip().toString() != localhost)
                    {
                        return ip;
                    }
                }
            }
        }

        return "";
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_serverWidget(nullptr)
    , m_myServer(nullptr)
{
    ui->setupUi(this);
    m_serverWidget = new ServerWidget(this);
    m_myServer = new MyServer(this);

    QString ip(GetIp());
    if(!ip.isEmpty())
    {
        ui->label->setText(QString("server ip: %0").arg(ip));
    }
    else
    {
        QMessageBox::critical(0, "Server Error", "Unable to get server ip");
    }

    connect (m_myServer, &MyServer::NewMsg, m_serverWidget, &ServerWidget::OnNewMsg);
}

MainWindow::~MainWindow()
{
    delete ui;
}
