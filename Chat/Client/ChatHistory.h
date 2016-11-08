#ifndef CHATHISTORY_H
#define CHATHISTORY_H

#include <QWidget>

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
    Ui::ChatHistory *ui;
};

#endif // CHATHISTORY_H
