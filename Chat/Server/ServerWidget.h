#pragma once

namespace Ui {
    class ServerWidget;
}

namespace qRpc {
    class ClientEmulated;
}

class ServerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ServerWidget(QWidget *parent = 0);
    ~ServerWidget();

public slots:
    void OnNewMsg(const QString& name, const QTime& time, const QString& msg);

private:
    std::unique_ptr<Ui::ServerWidget> m_ui;
};

