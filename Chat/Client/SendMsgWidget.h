#pragma once

namespace Ui {
    class SendMsgWidget;
}

class SendMsgWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SendMsgWidget(QWidget *parent = 0);
    ~SendMsgWidget();

signals:
    void SendMsg(const QString& msg);

private slots:
    void OnSendMsg();

private:
    void keyPressEvent(QKeyEvent* event);

private:
    std::unique_ptr<Ui::SendMsgWidget> m_ui;
};

