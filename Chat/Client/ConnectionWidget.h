#ifndef CONNECTIONWIDGET_H
#define CONNECTIONWIDGET_H

#include <QWidget>

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
    Ui::ConnectionWidget *ui;
};

#endif // CONNECTIONWIDGET_H
