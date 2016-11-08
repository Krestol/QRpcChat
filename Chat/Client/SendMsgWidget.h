#pragma once

#include <QWidget>

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
    Ui::SendMsgWidget *ui;
};

