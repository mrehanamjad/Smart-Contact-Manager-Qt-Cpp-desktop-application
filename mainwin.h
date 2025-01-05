#ifndef MAINWIN_H
#define MAINWIN_H

#include <QMainWindow>
#include <QString>

namespace Ui {
class MainWin;
}

class MainWin : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWin(QWidget *parent = nullptr);
    ~MainWin();
     void whichButtonActive(const QString &button);

private slots:
    void on_toAllContactBtn_clicked();

    void on_toAddContactBtn_clicked();

    void on_toSettingBtn_clicked();

private:
    Ui::MainWin *ui;
    QString setBtnStyle(const QString &Img, const QString &clr); // Declare here
};

#endif // MAINWIN_H
