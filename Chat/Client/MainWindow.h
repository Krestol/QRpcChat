#pragma once

namespace Ui
{
    class MainWindow;
}

enum Page
{
    PageConnection,
    PageWaiting,
    PageRegistration,
    PageSend
};

class ConnectionWidget;
class MyClient;
class WaitingWidget;
class SendMsgWidget;
class RegistrationWidget;
class ChatHistory;
class QTimer;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void OnConnectToServer(const QString& ip);
    void OnConnectedToServer();
    void OnChangeServer();
    void OnTryToRegistration(const QString& name);
    void OnSuccessfulRegistration(int id, const QString& name);
    void OnRegistrationFailed();

private:
    std::unique_ptr<Ui::MainWindow> m_ui;
    ConnectionWidget* m_connectionWidget;
    MyClient* m_client;
    WaitingWidget* m_waitingWidget;
    SendMsgWidget* m_sendMsgWidget;
    RegistrationWidget* m_registrationWidget;
    ChatHistory* m_historyWidget;
    QTimer* m_timer;
};

