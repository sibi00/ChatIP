#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>
#include "addnewnodepopup.h"
#include "infopopup.h"
#include "chatwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(QSize(350,600));

    fileMenu = menuBar()->addMenu(tr("&File"));
    infoMenu = menuBar()->addMenu(tr("&Info"));

    newNode = new QAction(tr("&Add node"), this);
    newNode->setShortcuts(QKeySequence::New);
    newNode->setStatusTip(tr("Adds new node to network"));
    fileMenu->addAction(newNode);
    connect(newNode, &QAction::triggered, this, &MainWindow::addNewNodePopup);

    info = new QAction(tr("&Abour"), this);
    info->setShortcuts(QKeySequence::New);
    info->setStatusTip(tr("Information about creator"));
    infoMenu->addAction(info);
    connect(info, &QAction::triggered, this, &MainWindow::infoPopup);



    bool ok = false;
    QString nickname =
            QInputDialog::getText(this, tr("Set nickname"), tr("User name:"),QLineEdit::Normal,"Mariusz", &ok);
    if (ok && !nickname.isEmpty())
    {
        ui->userLoggedLabel->setText(nickname);
        mNodesByName[nickname] = QHostAddress("127.0.0.1");
        setWindowTitle("ChatIP - Witaj "+nickname+" ;)");
    }


    socket = new QUdpSocket(this);
    socket->bind(QHostAddress::LocalHost, 1234);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::readyRead()
{
    QByteArray buffer;
    buffer.resize(socket->pendingDatagramSize());

    QHostAddress sender;
    quint16 senderPort;


    socket->readDatagram(buffer.data(), buffer.size(),&sender, &senderPort);
    qDebug()<<"Odebrano wiadomosc od adresu "<<sender<<" port "<<senderPort;
    if(mNodesByHostAddress.find(sender.toString()) != mNodesByHostAddress.end())
    {
        QString receivedMessageAsString(buffer);
        ChatWindow * receiverChatWindow = mChatWindowsByName[mNodesByHostAddress[sender.toString()]];
        receiverChatWindow->receivedMessage(receivedMessageAsString);
        receiverChatWindow->show();
    }
    else
    {
        qDebug()<<"Cos nie tak";

    }

}

void MainWindow::addNewNodePopup()
{
    mPopup = new addnewnodepopup(this);
    mPopup->show();

}

void MainWindow::infoPopup()
{
    mInfoPopupp = new InfoPopup(this);
    mInfoPopupp->show();
}
void MainWindow::addNewNode(QString pName,QString pAddress)
{
    ui->nodesListWidget->addItem(pName);
    mNodesByName[pName] = QHostAddress(pAddress);
    mNodesByHostAddress[pAddress] = pName;
    ChatWindow *  chat = new ChatWindow(this,pName, socket,mNodesByName[pName],ui->userLoggedLabel->text());
    chat->setWindowTitle(pName);
    mChatWindowsByName[pName] = chat;
}


void MainWindow::on_nodesListWidget_itemDoubleClicked(QListWidgetItem *item)
{

    mChatWindowsByName[item->text()]->show();
}

