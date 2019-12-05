#include <QCoreApplication>
#include <QDebug>
#include <QtSql>
#include "sqliteclass.h"
#include "globalDbObject.h"

#define ELECTRICAL_DEPARTMENT   1
#define MECHANICAL_DEPARTMENT   2
#define CIVIL_DEPARTMENT        3
#define ARCHITECTURE_DEPARTMENT 4



int main(int argc, char *argv[]){
    QCoreApplication a(argc, argv);

    qDebug() << "start";
    databaseInitialization();

    SQLiteClass SQLiteDb2 = SQLiteClass("db.sqlite");

    QString  table = "staff";
    QStringList columns = {"ID", "FullName", "Department"};
    QStringList columns2 = {"FullName", "Department"};
    QStringList types = {"INTEGER PRIMARY KEY AUTOINCREMENT", "TEXT", "INTEGER"};
    QStringList values = {"Gamal Abdelshafy", QString::number(ELECTRICAL_DEPARTMENT)};
    QStringList values2 = {"Ahmed Mohamed", QString::number(ELECTRICAL_DEPARTMENT)};

    SQLiteDb2.sql_create(table, columns, types);

    SQLiteDb2.sql_insert(table, columns2, values);
    SQLiteDb2.sql_insert(table, columns2, values);
    SQLiteDb2.sql_insert(table, columns2, values);
    SQLiteDb2.sql_insert(table, columns2, values);

    SQLiteDb2.sql_update(table, columns2, values2, "ID = 1");

    SQLiteDb2.sql_delete(table, "ID = 1");

    SQLiteDb2.sql_select("*", table, "");
    SQLiteDb2.sql_print();

    SQLiteDb2.sql_close();

    /*
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("F:/Ansary/QTProjects/Database/db.sqlite");

    if(!db.open()){
        qDebug() << "Problem while opening the database";
    }

    QString query = "CREATE TABLE staff ("
                    "ID INTEGER, "
                    "fullName VARCHAR(40), "
                    "birthday DATETIME, "
                    "department INTEGER);";
    QSqlQuery qry;

    if(!qry.exec(query)){
        qDebug() << "error while creating staff table";
    }

    AddValues(1, "Ayman Wahba", "01-01-1970", ELECTRICAL_DEPARTMENT);
    AddValues(2, "Bassem Amin", "11-11-1975", ELECTRICAL_DEPARTMENT);
    AddValues(3, "Gamal Abdelshafy", "13-05-1965",  ELECTRICAL_DEPARTMENT);

    db.close();
    */

    qDebug() << "end";

    return a.exec();
}


/*
void AddValues(int id, QString fullName, QString bd, int department){
    QSqlQuery qry;

    qry.prepare("INSERT INTO staff ("
                "ID, "
                "fullName, "
                "birthday, "
                "department) "
                "VALUES (?, ?, ?, ?);");
    qry.addBindValue(id);
    qry.addBindValue(fullName);
    qry.addBindValue(QDateTime::fromString(bd, "dd-mm-yyyy"));
    qry.addBindValue(department);

    if(!qry.exec()){
        qDebug() << "error while adding values to staff table";
    }
}
*/









