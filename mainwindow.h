#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork/QUdpSocket>
#include <QInputDialog>
#include <QListWidgetItem>
#include <chatwindow.h>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void addNewNode(QString pName,QString pAddress);
    void readyRead();
private slots:
    void addNewNodePopup();
    void infoPopup();
    void on_nodesListWidget_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;

    QMap<QString,QHostAddress> mNodesByName;
    QMap<QString,QString> mNodesByHostAddress;
    QMap<QString,ChatWindow*> mChatWindowsByName;
    QUdpSocket * socket;
    QDialog * mPopup;
    QDialog * mInfoPopupp;
    QMenu *fileMenu;
    QMenu *infoMenu;
    QAction * newNode;
    QAction * info;

};
#endif // MAINWINDOW_H
