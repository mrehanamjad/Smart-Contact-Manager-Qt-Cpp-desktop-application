#include "mainwindow.h"
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include "ui_mainwindow.h"
#include "mainwin.h"
#include "auth.h"
#include "contactmanager.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint | Qt::WindowMinimizeButtonHint);
    ui->signupErrorLabel->setAlignment(Qt::AlignCenter);
    ui->loginErrorLabel->setAlignment(Qt::AlignCenter);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openNextWindow(){
    MainWin *mainWin = new MainWin();
    mainWin->show();
    this->close();
}



void MainWindow::on_toLoginBtn_clicked()
{
    ui->tabWidget->setCurrentIndex(1);
}

void MainWindow::on_toSignupBtn_clicked()
{
    ui->tabWidget->setCurrentIndex(2);
}

void MainWindow::on_toSignupBtnInLoginPage_clicked()
{
    ui->tabWidget->setCurrentIndex(2);
}

void MainWindow::on_tologinBtnInSignupPage_clicked()
{
    ui->tabWidget->setCurrentIndex(1);
}

void MainWindow::on_loginBtn_clicked()
{
    QString email = ui->loginEmailInput->text().trimmed();
    QString password = ui->loginPasswordInput->text();

    Auth auth;
    QString loginRes = auth.login(email, password);

    if (loginRes == "true") {
        // ContactManager contactManager;
        openNextWindow();
    } else {
        ui->loginErrorLabel->setText(loginRes);
    }
}

void MainWindow::on_signupBtn_clicked()
{
    QString name = ui->signupNameInput->text().trimmed();
    QString email = ui->signupEmailInput->text().trimmed();
    QString password = ui->signupPasswordInput->text().trimmed();

    Auth auth;
    QString createdAccountRes = auth.createAccount(name, email, password);

    if (createdAccountRes == "true") {
        QString loginRes = auth.login(email, password);
        if (loginRes == "true") {
           openNextWindow();
        } else {
            ui->signupErrorLabel->setText("Failed to log in after account creation.");
        }
    } else {
        ui->signupErrorLabel->setText(createdAccountRes);
    }
}


void MainWindow::on_signupShowHidePasswordBtn_clicked()
{
    if(ui->signupShowHidePasswordBtn->text() == "Show Password"){
        ui->signupPasswordInput->setEchoMode(QLineEdit::Normal);
        ui->signupShowHidePasswordBtn->setText("Hide Password");
    } else {
        ui->signupPasswordInput->setEchoMode(QLineEdit::Password);
        ui->signupShowHidePasswordBtn->setText("Show Password");
    }
}

void MainWindow::on_loginShowHidePasswordBtn_clicked()
{
    if(ui->loginShowHidePasswordBtn->text() == "Show Password"){
        ui->loginPasswordInput->setEchoMode(QLineEdit::Normal);
        ui->loginShowHidePasswordBtn->setText("Hide Password");
    } else {
        ui->loginPasswordInput->setEchoMode(QLineEdit::Password);
        ui->loginShowHidePasswordBtn->setText("Show Password");
    }
}

