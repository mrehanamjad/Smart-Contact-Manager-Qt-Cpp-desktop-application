#include "contactmanager.h"

ContactManager::ContactManager() {
    bool isconnected = connectToDatabase();
    if(isconnected){
        getAllContacts();
    }
}

ContactManager::~ContactManager() {
    db.close();
}

bool ContactManager::connectToDatabase() {

    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("CMSDB");
    db.setUserName("root");
    db.setPassword("mysql");

    if (!db.open()) {
        qDebug() << "Database connection failed:" << db.lastError().text();
        return false;
    }
    return true;
}


bool ContactManager::addContact(const QString &name, const QString &phone, const QString &email, const QString &address, const QString &description) {
    QSqlQuery query;
    query.prepare("INSERT INTO contacts (user_id,name, phone, email, address,description) "
                  "VALUES (:userId,:name, :phone, :email, :address,description)");

    query.bindValue(":userId", userId);
    query.bindValue(":name", name);
    query.bindValue(":phone", phone);
    query.bindValue(":email", email);
    query.bindValue(":address", address);
    query.bindValue(":description", description);

    if (!query.exec()) {
        qDebug() << "Failed to add contact:" << query.lastError().text();
        return false;
    }
    return true;
}


bool ContactManager::editContact(int contactId, const QString &name, const QString &phone, const QString &email, const QString &address, const QString &description) {
    QSqlQuery query;
    query.prepare("UPDATE contacts SET name = :name, phone = :phone, email = :email, address = :address, description = :description "
                  "WHERE contact_id = :contactId");

    query.bindValue(":contactId", contactId);
    query.bindValue(":name", name);
    query.bindValue(":phone", phone);
    query.bindValue(":email", email);
    query.bindValue(":address", address);
    query.bindValue(":description",description);

    if (!query.exec()) {
        qDebug() << "Failed to edit contact:" << query.lastError().text();
        return false;
    }
    return true;
}

bool ContactManager::removeContact(int contactId) {
    QSqlQuery query;
    query.prepare("DELETE FROM contacts WHERE contact_id = :contactId");
    query.bindValue(":contactId", contactId);

    if (!query.exec()) {
        qDebug() << "Failed to remove contact:" << query.lastError().text();
        return false;
    }
    return true;
}

void ContactManager::getAllContacts() {

    // Query to get all contacts from the "contacts" table.
    QSqlQuery query("SELECT name, phone, email, address, description FROM contacts WHERE user_id = :userId");
    query.bindValue(":userId", userId);

    while (query.next()) {
        // Create a QStringList for each contact (row).
        QStringList contact;
        contact.append(query.value(0).toString());  // Name
        contact.append(query.value(1).toString());  // Phone
        contact.append(query.value(2).toString());  // Email
        contact.append(query.value(3).toString());  // Address
        contact.append(query.value(4).toString());  //description
        // Add the contact (row) to the contacts list (2D array).
        allContacts.append(contact);
    }
}

