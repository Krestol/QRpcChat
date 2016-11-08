#pragma once

#include <QMainWindow>

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
    Ui::MainWindow *ui;
    ServerWidget* m_serverWidget;
    MyServer* m_myServer;
};

