#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

    void on_signupBtn_clicked();

    void on_signupShowHidePasswordBtn_clicked();

    void on_loginShowHidePasswordBtn_clicked();

private:
    Ui::MainWindow *ui;


    void openNextWindow();
};
#endif // MAINWINDOW_H
