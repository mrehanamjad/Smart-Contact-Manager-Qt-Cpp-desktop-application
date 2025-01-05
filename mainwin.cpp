#include "mainwin.h"
#include "ui_mainwin.h"
#include <QHeaderView>

MainWin::MainWin(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWin)
{
    ui->setupUi(this);

    // Resize columns to contents
    for (int i = 0; i < ui->tableWidget->columnCount(); ++i) {
        ui->tableWidget->horizontalHeader()->setSectionResizeMode(i, QHeaderView::ResizeToContents);
    }
}

MainWin::~MainWin()
{
    delete ui;
}

QString MainWin::setBtnStyle(const QString &Img, const QString &clr) {
    return QString(
               "image: url(%1);"
               "background-color: %2;"
               "border: none;"
               "padding: 15px;"
               ).arg(Img).arg(clr);
}

void MainWin::whichButtonActive(const QString &button) {
    if (button == "toAllContactBtn") {
        ui->toAllContactBtn->setStyleSheet(setBtnStyle(":/asserts/contact-list.png", "white"));
        ui->toAddContactBtn->setStyleSheet(setBtnStyle(":/asserts/add-user.png", "orange"));
        ui->toSettingBtn->setStyleSheet(setBtnStyle(":/asserts/settings.png", "orange"));
    } else if (button == "toAddContactBtn") {
        ui->toAllContactBtn->setStyleSheet(setBtnStyle(":/asserts/contact-list.png", "orange"));
        ui->toAddContactBtn->setStyleSheet(setBtnStyle(":/asserts/add-user.png", "white"));
        ui->toSettingBtn->setStyleSheet(setBtnStyle(":/asserts/settings.png", "orange"));
    } else if (button == "toSettingBtn") {
        ui->toAllContactBtn->setStyleSheet(setBtnStyle(":/asserts/contact-list.png", "orange"));
        ui->toAddContactBtn->setStyleSheet(setBtnStyle(":/asserts/add-user.png", "orange"));
        ui->toSettingBtn->setStyleSheet(setBtnStyle(":/asserts/settings.png", "white"));
    }
}


void MainWin::on_toAllContactBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    whichButtonActive("toAllContactBtn");
}

void MainWin::on_toAddContactBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    whichButtonActive("toAddContactBtn");
}

void MainWin::on_toSettingBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    whichButtonActive("toSettingBtn");
}
