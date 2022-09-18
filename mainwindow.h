#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork/QUdpSocket>

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

    void on_debugSendText_clicked();

    void on_debugSendLineEdit_returnPressed();

private:
    Ui::MainWindow *ui;

    QMap<QString,QString> nodes;
    QUdpSocket * socket;
    QDialog * mPopup;
    QMenu *fileMenu;
    QAction * newNode;
};
#endif // MAINWINDOW_H
