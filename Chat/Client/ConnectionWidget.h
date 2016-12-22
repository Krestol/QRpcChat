#pragma once

namespace Ui {
    class ConnectionWidget;
}

class ConnectionWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ConnectionWidget(QWidget *parent);
    ~ConnectionWidget();

signals:
    void ConnectToServer(const QString& ip);

private slots:
    void OnConnect();

private:
     void keyPressEvent(QKeyEvent* event);

private:
    std::unique_ptr<Ui::ConnectionWidget> m_ui;
};

