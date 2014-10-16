#include "db.h"

QSqlDatabase g_db;

#define DB_PATH "c:\\Projects\\game\\db\\game_storage.sqlite"

QSqlDatabase GetDb() {
    static bool init = false;
    if (!init) {
        g_db = QSqlDatabase::addDatabase("QSQLITE", "my_db");
        g_db.setDatabaseName(DB_PATH);
        if (!g_db.open()) {
            qDebug("Failed to open database");
        } else {
            init = true;
        }
    }
    return g_db;
}
