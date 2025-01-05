#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mainwin.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_toLoginBtn_clicked();

    void on_toSignupBtn_clicked();

    void on_toSignupBtnInLoginPage_clicked();

    void on_tologinBtnInSignupPage_clicked();

    void on_loginBtn_clicked();

private:
    Ui::MainWindow *ui;
    MainWin *mainWinUi;
};
#endif // MAINWINDOW_H
