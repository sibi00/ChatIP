#ifndef INFOPOPUP_H
#define INFOPOPUP_H

#include <QDialog>

namespace Ui {
class InfoPopup;
}

class InfoPopup : public QDialog
{
    Q_OBJECT

public:
    explicit InfoPopup(QWidget *parent = nullptr);
    ~InfoPopup();

private slots:
    void on_okPushButton_pressed();

private:
    Ui::InfoPopup *ui;
};

#endif // INFOPOPUP_H
