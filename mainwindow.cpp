#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>
#include "addnewnodepopup.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    fileMenu = menuBar()->addMenu(tr("&File"));
    newNode = new QAction(tr("&Add node"), this);
    newNode->setShortcuts(QKeySequence::New);
    newNode->setStatusTip(tr("Adds new node to network"));
    fileMenu->addAction(newNode);
    connect(newNode, &QAction::triggered, this, &MainWindow::addNewNodePopup);

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
    // when data comes in
    QByteArray buffer;
    buffer.resize(socket->pendingDatagramSize());

    QHostAddress sender;
    quint16 senderPort;

    // qint64 QUdpSocket::readDatagram(char * data, qint64 maxSize,
    //                 QHostAddress * address = 0, quint16 * port = 0)
    // Receives a datagram no larger than maxSize bytes and stores it in data.
    // The sender's host address and port is stored in *address and *port
    // (unless the pointers are 0).

    socket->readDatagram(buffer.data(), buffer.size(),&sender, &senderPort);
    ui->debugTextBrowser->append("rx: "+ buffer);
    qDebug() << "Message from: " << sender.toString();
    qDebug() << "Message port: " << senderPort;
    qDebug() << "Message: " << buffer;
}

void MainWindow::addNewNodePopup()
{
    mPopup = new addnewnodepopup(this);
    mPopup->show();

}
void MainWindow::addNewNode(QString pName,QString pAddress)
{
    ui->nodesListWidget->addItem(pName);

}

void MainWindow::on_debugSendText_clicked()
{
    QByteArray data;
    QString text = ui->debugSendLineEdit->text();
    data.append(text.toStdString());

    if(data.size() != 0)
    {
        socket->writeDatagram(data, QHostAddress::LocalHost, 1234);
        ui->debugTextBrowser->append("tx: "+ data);
        ui->debugSendLineEdit->clear();
    }

}


void MainWindow::on_debugSendLineEdit_returnPressed()
{
    on_debugSendText_clicked();
}

