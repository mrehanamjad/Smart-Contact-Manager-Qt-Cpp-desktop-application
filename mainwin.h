#ifndef MAINWIN_H
#define MAINWIN_H

#include <QMainWindow>
#include <QString>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QtSql/QSqlDatabase>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <QDesktopServices>
#include <QUrl>
#include <QJsonArray>

namespace Ui {
class MainWin;
}

class MainWin : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWin(QWidget *parent = nullptr);
    ~MainWin();

private slots:
    void on_toAllContactBtn_clicked();

    void on_toAddContactBtn_clicked();

    void on_toSettingBtn_clicked();

    void on_addContactBtn_clicked();

    void on_toEditBtn_clicked();

    void on_editContactBtn_clicked();

    void on_DeleteContactBtn_clicked();

    void on_logoutBtn_clicked();

    void on_editAccountBtn_clicked();

    void on_showHideChangePasswordBtn_clicked();

    void on_changePassworBtn_clicked();

    void on_toEdituserInfoBtn_clicked();

    void on_toChangePassword_clicked();

    void on_toUserInfoBtn_clicked();

    void on_toDeleteAccount_clicked();

    void on_searchInput_textChanged(const QString &arg1);

    void on_sendEmailBtn_clicked();

    void on_toSendEmailBtn_clicked();

    void on_cancelSendEmailBtn_clicked();

    void on_deleteAccountBtn_clicked();

private:
    Ui::MainWin *ui;
    QNetworkAccessManager *networkManager;

    void openNextWindow();
    QString setBtnStyle(const QString &Img, const QString &clr);

    void whichButtonActive(const QString &button);
    void InsertRowToTable(QStringList contact);
    void InsertDataInTable();
    QStringList getSelectedRow();
    void setUserDataInUi();
    void whichButtonActiveOnAccountSettingTab(const QString &button);
    QString setAccountSettingNavBtnStyle(const QString &clr);
    QList<QStringList> getMultipleSelectedRows();
    void onNetworkReplyFinished(QNetworkReply *reply);
};

#endif // MAINWIN_H
