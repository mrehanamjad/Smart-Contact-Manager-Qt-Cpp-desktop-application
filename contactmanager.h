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

class ContactManager
{
public:
    ContactManager();
    ~ContactManager();
    QList<QStringList> allContacts;

    bool addContact(const QString &name, const QString &phone, const QString &email, const QString &address, const QString &description);
    bool removeContact(int contactId);
    bool editContact(int contactId, const QString &name, const QString &phone, const QString &email, const QString &address, const QString &description);

private:
    QString userId;
    QSqlDatabase db;
    void getAllContacts();
    bool connectToDatabase();
};

#endif // CONTACTMANAGER_H
