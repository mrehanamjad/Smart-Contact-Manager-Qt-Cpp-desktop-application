#include "auth.h"
#include "contactmanager.h"
#include "databasemanager.h"
#include <QSettings>

Auth::Auth() {}

Auth::~Auth() {}

QString Auth::hashPassword(const QString &password) {
    QByteArray hashed = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256);
    return hashed.toHex();
}

bool Auth::isEmailValid(const QString &email) {
    return email.isLower() && email.contains('@') && email.contains('.');
}

bool Auth::isPasswordStrong(const QString &password) {
    return password.length() >= 8;
}

QString Auth::createAccount(const QString &name, const QString &email, const QString &password) {
    if (name.isEmpty() || email.isEmpty() || password.isEmpty()) {
        return "All fields are required.";
    }

    if (!isEmailValid(email)) {
        return "Invalid email format.";
    }

    if (!isPasswordStrong(password)) {
        return "Password must be at least 8 characters long.";
    }

    QString randomId = QUuid::createUuid().toString(QUuid::WithoutBraces);
    QSqlDatabase db = DatabaseManager::getDatabase();

    if (!db.isOpen()) {
        return "Database connection error.";
    }

    QSqlQuery query(db);
    query.prepare("INSERT INTO users (user_id, name, email, password) VALUES (:userId, :name, :email, :password)");
    query.bindValue(":userId", randomId);
    query.bindValue(":name", name);
    query.bindValue(":email", email);
    query.bindValue(":password", hashPassword(password));

    if (!query.exec()) {
        QString dbError = query.lastError().text();
        qDebug() << "Registration query failed:" << dbError;
        if (dbError.contains("Duplicate entry", Qt::CaseInsensitive)) {
            return "A user with this email already exists.";
        }
        return "Database error during registration.";
    }

    return "true";
}

QString Auth::login(const QString &email, const QString &password) {
    if (email.isEmpty() || password.isEmpty()) {
        return "All fields are required.";
    }

    if (!isEmailValid(email)) {
        return "Invalid email format.";
    }

    QSqlDatabase db = DatabaseManager::getDatabase();

    if (!db.isOpen()) {
        return "Database connection error.";
    }

    QSqlQuery query(db);
    query.prepare("SELECT user_id, password FROM users WHERE email = :email");
    query.bindValue(":email", email);

    if (!query.exec()) {
        qDebug() << "Login query failed:" << query.lastError().text();
        return "Database error during login.";
    }

    if (query.next()) {
        QString storedHash = query.value(1).toString();
        if (storedHash == hashPassword(password)) {
            QString id = query.value(0).toString();
            this->userId = id;
            QSettings settings("MyCompany", "MyApp");
            settings.setValue("userId", userId);
            return "true";
        } else {
            return "Incorrect password.";
        }
    } else {
        return "No account with this email found.";
    }
}

QStringList Auth::getAccountData() {

    if(this->userId.isEmpty()){
        setUserId();
    }

    QSqlDatabase db = DatabaseManager::getDatabase();

    if (!db.isOpen()) {
        qDebug() << "error" << "Database connection error.";
        return QStringList();;
    }

    QSqlQuery query(db);
    query.prepare("SELECT name, password, email, phone_number, created_at FROM users WHERE user_id = :userId");
    query.bindValue(":userId", this->userId);

    if (!query.exec()) {
        qDebug() << "Get account data query failed:" << query.lastError().text();
        return QStringList();
    }

    if (query.next()) {
        QStringList accountData{
            query.value(0).toString(),
            query.value(1).toString(),
            query.value(2).toString(),
            query.value(3).toString(),
            query.value(4).toString()
        };
        return accountData;
    } else {
        return QStringList();
    }
}

QString Auth::editAccount(const QString& name, const QString& phone) {

    if(this->userId.isEmpty()){
        setUserId();
    }

    if (name.isEmpty()) {
        return "Name is required.";
    }


    QSqlDatabase db = DatabaseManager::getDatabase();
    if (!db.isOpen()) {
        return "Database connection error.";
    }

    // Prepare and execute the SQL query
    QSqlQuery query(db);
    query.prepare(
        "UPDATE users SET name = :name, phone_number = :phone WHERE user_id = :userId"
        );
    query.bindValue(":name", name);
    query.bindValue(":phone", phone);
    query.bindValue(":userId", this->userId); // Ensure userId is valid

    if (!query.exec()) {
        qDebug() << "Edit account query failed:" << query.lastError().text();
        return "Failed to update account details.";
    }

    return "true";
}

QString Auth::changePassword(const QString& oldPassword, const QString& newPassword, const QString& confirmPassword) {
    if (oldPassword.isEmpty() || newPassword.isEmpty() || confirmPassword.isEmpty()) {
        return "All fields are required.";
    }

    if (newPassword != confirmPassword) {
        return "New password and confirmation password do not match.";
    }

    if (oldPassword == newPassword) {
        return "The new password cannot be the same as the old password.";
    }

    QStringList accountData = getAccountData();
    if (accountData.size() < 2) {
        return "Failed to retrieve account data.";
    }

    if (hashPassword(oldPassword) != accountData[1]) {
        return "Incorrect old password.";
    }

    QString hashedNewPassword = hashPassword(newPassword);

    QSqlDatabase db = DatabaseManager::getDatabase();
    if (!db.isOpen()) {
        return "Database connection error.";
    }

    QSqlQuery query(db);
    query.prepare("UPDATE users SET password = :pass WHERE user_id = :userId");
    query.bindValue(":pass", hashedNewPassword);
    query.bindValue(":userId", this->userId);

    if (!query.exec()) {
        qDebug() << "Password update query failed:" << query.lastError().text();
        return "Failed to update the password.";
    }

    return "true";
}

QString Auth::deleteAccount(const QString &password) {
    if (password.isEmpty()) {
        return "Password is required to delete your account.";
    }

    if (this->userId.isEmpty()) {
        setUserId();
    }

    QStringList accountData = getAccountData();
    if (accountData.size() < 2) {
        return "Failed to retrieve account data.";
    }

    QString hashedPassword = hashPassword(password);
    if (hashedPassword != accountData[1]) {
        return "Incorrect password. Account deletion failed.";
    }

    QSqlDatabase db = DatabaseManager::getDatabase();
    if (!db.isOpen()) {
        return "Database connection error.";
    }

    QSqlQuery query(db);
    query.prepare("DELETE FROM contacts WHERE user_id = :userId; DELETE FROM users WHERE user_id = :userId; ");
    query.bindValue(":userId", this->userId);

    if (!query.exec()) {
        qDebug() << "Account deletion query failed:" << query.lastError().text();
        return "Failed to delete the account.";
    }

    return "true";
}


void Auth::setUserId(){
    QSettings settings("MyCompany", "MyApp");
    QString id = settings.value("userId").toString();
    this->userId = id;
}


QString Auth::getUserId() {
    return this->userId;
}

bool Auth::logout() {
    QSettings settings("MyCompany", "MyApp");
    settings.remove("userId");
    this->userId.clear();
    return true;
}
