#ifndef AUTH_H
#define AUTH_H

#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QCryptographicHash>
#include <QByteArray>
#include <QUuid>
#include <QSettings>
#include <QStringList>

class Auth
{
public:
    Auth();
    ~Auth();

    QString getUserId();
    QString  createAccount(const QString &name, const QString &email, const QString &password);
    QString login(const QString &email, const QString &password);
    bool logout();
    bool connectToDatabase();
    QStringList getAccountData();
    QString editAccount(const QString &name, const QString &phone);
    QString changePassword(const QString &oldPassword, const QString &newPassword, const QString &confirmPassword);
    QString deleteAccount(const QString &password);

private:
    QString userId;
    QSqlDatabase db;
    QString hashPassword(const QString &password);
    bool isEmailValid(const QString &email);
    bool isPasswordStrong(const QString &password);
    void setUserId();
};

#endif // AUTH_H
