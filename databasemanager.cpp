#include "databasemanager.h"

QSqlDatabase DatabaseManager::getDatabase() {
    static QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    if (!db.isOpen()) {
        db.setHostName("localhost");
        db.setPort(3306);
        db.setDatabaseName("CMSDB");
        db.setUserName("root");
        db.setPassword("mysql");
        if (!db.open()) {
            qDebug() << "Database connection failed:" << db.lastError().text();
        } else {
            qDebug() << "Database connection successful!";
        }
    }
    return db;
}

DatabaseManager::DatabaseManager() {
}
