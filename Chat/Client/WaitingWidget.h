#pragma once

namespace Ui {
    class WaitingWidget;
}

class WaitingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit WaitingWidget(QWidget *parent);
    ~WaitingWidget();

    void Show(const QString& ip);

signals:
    void ChangeServer();

private:
    std::unique_ptr<Ui::WaitingWidget> m_ui;
};
