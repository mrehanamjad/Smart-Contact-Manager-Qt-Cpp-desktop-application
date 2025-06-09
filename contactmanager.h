#ifndef CONTACTMANAGER_H
#define CONTACTMANAGER_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QString>
#include <QList>
#include <QStringList>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QtSql/QSqlDatabase>
#include <QSettings>

class ContactManager
{
public:
    ContactManager();
    ~ContactManager();
    QList<QStringList> allContacts;

    QString addContact(const QString &name, const QString &phone, const QString &email, const QString &address, const QString &description);
    QString removeContact(int contactId);
    QString editContact(int contactId, const QString &name, const QString &phone, const QString &email, const QString &address, const QString &description);
    QList<QStringList> merge(const QList<QStringList> &left, const QList<QStringList> &right, int columnIndex);
    QList<QStringList> mergeSort(QList<QStringList> data, int columnIndex);
    QList<QStringList> searchContact(const QString &keyword);

private:
    QString userId;
    QSqlDatabase db;
    void getAllContacts();
    void setUserId();

};

#endif
