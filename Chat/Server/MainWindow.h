#pragma once

namespace Ui {
    class MainWindow;
}

class MyServer;
class ServerWidget;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    std::unique_ptr<Ui::MainWindow> m_ui;
    ServerWidget* m_serverWidget;
    MyServer* m_myServer;
};

