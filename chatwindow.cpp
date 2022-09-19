#include "chatwindow.h"
#include "ui_chatwindow.h"

ChatWindow::ChatWindow(QWidget *parent,
                       QString name,
                       QUdpSocket* socket,
                       QHostAddress hostAddress,
                       QString localName) :
    QDialog(parent),
    ui(new Ui::ChatWindow),
    mSocket(socket),
    mName(name),
    mHostAddress(hostAddress),
    mLoggedUserName(localName)

{
    ui->setupUi(this);
}

ChatWindow::~ChatWindow()
{
    delete ui;
}

void ChatWindow::on_sentButton_clicked()
{

            QByteArray data;
            QString text = ui->inputSentText->text();
            data.append(text.toStdString());

            if(data.size() != 0)
            {
                qInfo()<<"Uzytkownik "<<mLoggedUserName<<" wysyla wiadomosc o tresci: "<<
                         text<<" na adres "<<mHostAddress<<" port "<<1234;
                mSocket->writeDatagram(data, mHostAddress, 1234);
                ui->conversationTextField->append(mLoggedUserName+": "+ data);
                ui->inputSentText->clear();
            }
}

void ChatWindow::receivedMessage(QString msg)
{
    qInfo()<<"Uzytkownik "<<mLoggedUserName<<" odebrał waidomosc o tresci: "<< msg;
    ui->conversationTextField->append(mName+": "+ msg);
}

