#include "contactmanager.h"
#include "databasemanager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include "auth.h"
#include <QSettings>

ContactManager::ContactManager() {
    setUserId();
    getAllContacts();
}

ContactManager::~ContactManager() {}


void ContactManager::setUserId(){
    QSettings settings("MyCompany", "MyApp");
    QString id = settings.value("userId").toString();
    this->userId = id;
}




QString ContactManager::addContact(const QString &name, const QString &phone, const QString &email, const QString &address, const QString &description) {
    if (this->userId.isEmpty()) {
        qDebug() << "Error: userId is not set.";
        return "User ID is not set. Please log in.";
    }

    QSqlDatabase db = DatabaseManager::getDatabase();

    if (!db.isOpen()) {
        return "Database connection error.";
    }

    QSqlQuery query(db);
    query.prepare("INSERT INTO contacts (user_id, name, phone, email, address, description) "
                  "VALUES (:userId, :name, :phone, :email, :address, :description)");

    query.bindValue(":userId", this->userId);
    query.bindValue(":name", name);
    query.bindValue(":phone", phone);
    query.bindValue(":email", email);
    query.bindValue(":address", address);
    query.bindValue(":description", description);

    if (!query.exec()) {
        QString dbError = query.lastError().text();
        qDebug() << "Failed to add contact. Database error:" << dbError;

        if (dbError.contains("Duplicate entry", Qt::CaseInsensitive)) {
            return "A contact with this phone or email already exists.";
        }
        return "Failed to add contact.\nError: " + dbError;
    }

    getAllContacts();
    return "true";
}

QString ContactManager::editContact(int contactId, const QString &name, const QString &phone, const QString &email, const QString &address, const QString &description) {
    QSqlDatabase db = DatabaseManager::getDatabase();

    if (!db.isOpen()) {
        return "Database connection error.";
    }

    QSqlQuery query(db);
    query.prepare("UPDATE contacts SET name = :name, phone = :phone, email = :email, address = :address, description = :description "
                  "WHERE contact_id = :contactId");
    query.bindValue(":contactId", contactId);
    query.bindValue(":name", name);
    query.bindValue(":phone", phone);
    query.bindValue(":email", email);
    query.bindValue(":address", address);
    query.bindValue(":description", description);

    if (!query.exec()) {
        qDebug() << "Failed to edit contact:" << query.lastError().text();
        return "Failed to edit contact.\nError: " + query.lastError().text();
    }

    getAllContacts();
    return "true";
}

QString ContactManager::removeContact(int contactId) {
    QSqlDatabase db = DatabaseManager::getDatabase();

    if (!db.isOpen()) {
        return "Database connection error.";
    }

    QSqlQuery query(db);
    query.prepare("DELETE FROM contacts WHERE contact_id = :contactId");
    query.bindValue(":contactId", contactId);

    if (!query.exec()) {
        qDebug() << "Failed to remove contact:" << query.lastError().text();
        return "Failed to delete contact.\nError: " + query.lastError().text();
    }

    getAllContacts();
    return "true";
}

QList<QStringList> ContactManager::merge(const QList<QStringList> &left, const QList<QStringList> &right, int columnIndex) {
    QList<QStringList> result;
    int i = 0, j = 0;

    while (i < left.size() && j < right.size()) {
        if(left[i][columnIndex] < right[j][columnIndex]){
            result.append(left[i]);
            i++;
        } else {
            result.append(right[j]);
            j++;
        }
    }

    // Append remaining elements
    while (i < left.size()) {
        result.append(left[i]);
        i++;
    }
    while (j < right.size()) {
        result.append(right[j]);
        j++;
    }

    return result;
}

// Merge Sort function
QList<QStringList> ContactManager::mergeSort(QList<QStringList> data, int columnIndex) {
    if (data.size() <= 1) {
        return data;
    }

    int mid = data.size() / 2;
    QList<QStringList> left = data.mid(0, mid);
    QList<QStringList> right = data.mid(mid);

    left = mergeSort(left, columnIndex);
    right = mergeSort(right, columnIndex);

    return merge(left, right, columnIndex);
}



void ContactManager::getAllContacts() {
    this->allContacts.clear();

    QSqlDatabase db = DatabaseManager::getDatabase();

    if (!db.isOpen()) {
        qDebug() << "Database connection error.";
        return;
    }

    QSqlQuery query(db);
    query.prepare("SELECT contact_id, name, phone, email, address, description FROM contacts WHERE user_id = :userId");
    query.bindValue(":userId", this->userId);

    if (!query.exec()) {
        qDebug() << "Error fetching contacts:" << query.lastError().text();
        return;
    }

    while (query.next()) {
        QStringList contact{
            query.value(0).toString(),  // Contact ID
            query.value(1).toString(),  // Name
            query.value(2).toString(),  // Phone
            query.value(3).toString(),  // Email
            query.value(4).toString(),  // Address
            query.value(5).toString()   // Description
        };
        this->allContacts.append(contact);
    }

    this->allContacts = mergeSort(this->allContacts,1);
}

QList<QStringList> ContactManager::searchContact(const QString &keyword) {
    QList<QStringList> searchResults;

    if (this->userId.isEmpty()) {
        qDebug() << "Error: userId is not set.";
        return searchResults;
    }

    QSqlDatabase db = DatabaseManager::getDatabase();

    if (!db.isOpen()) {
        qDebug() << "Database connection error.";
        return searchResults;
    }

    QSqlQuery query(db);

    query.prepare("SELECT contact_id, name, phone, email, address, description FROM contacts WHERE user_id = :userId AND (name LIKE :keyword OR phone LIKE :keyword OR email LIKE :keyword OR address LIKE :keyword OR description LIKE :keyword)");
    query.bindValue(":userId", this->userId);
    query.bindValue(":keyword", "%" + keyword + "%"); // Wildcard for partial matching

    if (!query.exec()) {
        qDebug() << "Error searching contacts:" << query.lastError().text();
        return searchResults; // Return empty on query failure
    }

    // Populate results
    while (query.next()) {
        QStringList contact{
            query.value(0).toString(), // Contact ID
            query.value(1).toString(), // Name
            query.value(2).toString(), // Phone
            query.value(3).toString(), // Email
            query.value(4).toString(), // Address
            query.value(5).toString()  // Description
        };
        searchResults.append(contact);
    }

    return searchResults;
}
