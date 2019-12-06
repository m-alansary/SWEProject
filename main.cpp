#include <QCoreApplication>
#include <QDebug>
#include <QtSql>
#include "sqliteclass.h"
#include "globalDbObject.h"

int main(int argc, char *argv[]){
    QCoreApplication a(argc, argv);

    qDebug() << "start";
    databaseInitialization();

    qDebug() << "end";

    return a.exec();
}









