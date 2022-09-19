#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QDialog>
#include <QUdpSocket>
namespace Ui {
class ChatWindow;
}

class ChatWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ChatWindow(QWidget *parent = nullptr,
                        QString item = "",
                        QUdpSocket* socket = 0,
                        QHostAddress hostAddress = QHostAddress::SpecialAddress::Null,
                        QString loggedUserName = "");
    ~ChatWindow();
public slots:
    void receivedMessage(QString msg);
private slots:
    void on_sentButton_clicked();

private:
    Ui::ChatWindow *ui;
    QUdpSocket * mSocket;
    QString mName;
    QString mLoggedUserName;
    QHostAddress mHostAddress;
};

#endif // CHATWINDOW_H
