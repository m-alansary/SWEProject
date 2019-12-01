#include "sqliteclass.h"

SQLiteClass::SQLiteClass(QString dbName)
{
    db = QSqlDatabase::addDatabase("QSQLITE");

    QString dbPath = QDir::currentPath();

    dbPath += "/" + dbName;

    qDebug() << dbPath;

    db.setDatabaseName(dbPath);

    if(!db.open()){
        qDebug() << "Problem while opening the database";
    }

    QSqlQuery qry;
    query = qry;
}

int SQLiteClass::sql_create(QString table, QStringList columns, QStringList types){
    QString sql = QString("CREATE TABLE ") + table + "(";
    QString temp = "";

    int size = columns.size();
    for(int i = 0; i < size; i++){
        temp += columns.at(i) + " " + types.at(i) + ",";
    }
    temp.chop(1);

    sql += temp + ");";

    if(!query.exec(sql)){
        qDebug() << "error while creating";
    }

    return 0;
}


int SQLiteClass::sql_select(QString select, QString from, QString where){
    QString sql = QString("SELECT ") + select + QString(" FROM ") + from;
    if(where == ""){
        sql += QString(";");
    }
    else{
         sql += QString(" WHERE ") + where + QString(";");
    }
    //qDebug() << sql;

    if(!query.exec(sql)){
        qDebug() << "error while selecting";
    }

    return 0;
}

int SQLiteClass::sql_insert(QString table, QStringList columns, QStringList values){
    QString sql = QString("INSERT INTO ") + table + QString(" ( ");
    QString co = "";
    QString vl = "";
    int size = columns.size();
    for(int i = 0; i < size; i++){
        co += QString("`") + columns.at(i) + QString("`") + QString(",");
        vl += QString("'") + values.at(i) + QString("'") + QString(",");
        //vl += "?,";
        //query.addBindValue(values.at(i));
    }

    co.chop(1);
    vl.chop(1);


    sql += co + QString(") ") + QString("VALUES(") + vl + QString(");");

    //qDebug() << sql;

    if(!query.exec(sql)){
        qDebug() << "error while inserting";
    }

    return query.numRowsAffected();
}

int SQLiteClass::sql_update(QString table, QStringList columns, QStringList values, QString where){

    QString sql = QString("UPDATE `") + table + QString("` SET ")  ;
    QString temp = "";

    int size = columns.size();
    for(int i = 0; i < size; i++){
        temp = temp + QString("`") + columns.at(i) + QString("`") + QString("=") + "'" + values.at(i) + "'" + QString(",");
        //query.addBindValue(values.at(i));
    }

    temp.chop(1);
    sql = sql + temp + QString(" WHERE ") + where;
    //qDebug() << sql;


    if(!query.exec(sql)){
        qDebug() << "error while updating";
    }
    return query.numRowsAffected();
}


int SQLiteClass::sql_delete(QString table, QString where){
    QString sql = QString("DELETE ") + QString("FROM ") + table + QString(" WHERE ") + where ;
    //qDebug() << sql;
    QSqlQuery qry;
    qry.exec(sql);
    query = qry;
    return 0;
}

int SQLiteClass::sql_print(){
    while (query.next()) {
        int id = query.value(0).toInt();
        QString name = query.value(1).toString();
        int department = query.value(2).toInt();
        qDebug() << id << name << department;
    }
    return 0;
}

QSqlQuery SQLiteClass::sql_getQuery(){
    return query;
}


int SQLiteClass::sql_close(){
    db.close();
    return 0;
}


