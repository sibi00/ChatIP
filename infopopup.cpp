#include "infopopup.h"
#include "ui_infopopup.h"

InfoPopup::InfoPopup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InfoPopup)
{
    ui->setupUi(this);
    QString info ="Mariusz Sobiecki";
    ui->creatorInfoTextBrowser->setText(info);
}

InfoPopup::~InfoPopup()
{
    delete ui;
}

void InfoPopup::on_okPushButton_pressed()
{
    this->close();
}

