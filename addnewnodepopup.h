#ifndef ADDNEWNODEPOPUP_H
#define ADDNEWNODEPOPUP_H

#include <QDialog>
namespace Ui {
class addnewnodepopup;
}

class addnewnodepopup : public QDialog
{
    Q_OBJECT

public:
    explicit addnewnodepopup(QWidget *parent = nullptr);
    ~addnewnodepopup();
signals:
    void newNodeAddedButtonClicked(QString name,QString address);
private slots:
    void on_addNewNodeButton_clicked();

private:
    Ui::addnewnodepopup *ui;
    QWidget * parent;
};

#endif // ADDNEWNODEPOPUP_H
