#pragma once

namespace Ui {
    class RegistrationWidget;
}

class RegistrationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RegistrationWidget(QWidget *parent);
    ~RegistrationWidget();

    void WaitWhileRegistrate();
    void AskForAnotherName();

signals:
    void Registration(const QString& name);

private slots:
    void OnRegistration();

private:
    void keyPressEvent(QKeyEvent* event);

private:
    std::unique_ptr<Ui::RegistrationWidget> m_ui;
};

