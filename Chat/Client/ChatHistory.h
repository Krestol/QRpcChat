#pragma once

namespace Ui {
    class ChatHistory;
}

class Message;
class ChatHistory : public QWidget
{
    Q_OBJECT

public:
    explicit ChatHistory(QWidget *parent = 0);
    ~ChatHistory();

public slots:
    void SetHistory(const std::vector<Message>& history);

private:
    std::unique_ptr<Ui::ChatHistory> m_ui;
};

