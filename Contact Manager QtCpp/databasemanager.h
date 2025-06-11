#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>

class DatabaseManager
{
public:
    static QSqlDatabase getDatabase();
private:
    DatabaseManager();
};

#endif // DATABASEMANAGER_H
