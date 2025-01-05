#include "mainwindow.h"
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QtSql/QSqlDatabase>
#include "ui_mainwindow.h"

void connectToDatabase()
{
    // Create a database connection
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setPort(3306);
    db.setDatabaseName("CMSDB"); // Replace with your database name
    db.setUserName("root");      // Replace with your MySQL username
    db.setPassword("mysql");     // Replace with your MySQL password

    // Open the connection
    if (!db.open()) {
        qDebug() << "Database connection failed:" << db.lastError().text();
    } else {
        qDebug() << "Database connection successful!";
    }
}

void checkDrivers()
{
    QStringList drivers = QSqlDatabase::drivers();
    qDebug() << "Available drivers:" << drivers;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    checkDrivers();
    connectToDatabase();
    this->setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint);
}

MainWindow::~MainWindow()
{
    delete ui;
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
    mainWinUi = new MainWin(this);
    mainWinUi->show();
}

