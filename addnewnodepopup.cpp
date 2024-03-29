#include "addnewnodepopup.h"
#include "ui_addnewnodepopup.h"
#include <QDebug>

addnewnodepopup::addnewnodepopup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addnewnodepopup),
    parent(parent)
{
    ui->setupUi(this);
    setWindowModality(Qt::ApplicationModal); // blokuje okno glowne
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint); // Uniemozliwia resize
}

addnewnodepopup::~addnewnodepopup()
{
    delete ui;
}

void addnewnodepopup::on_addNewNodeButton_clicked()
{
    QString name = ui->nodeNameLineEdit->text();
    QString address = ui->nodeAddressLineEdit->text();
    emit newNodeAddedButtonClicked(name,address);
    this->close();
}

