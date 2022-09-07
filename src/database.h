#ifndef DATABASE_H
#define DATABASE_H

#include <QDebug>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

QSqlError createDb(QString databasepath)
{
  QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
  db.setDatabaseName(databasepath);
  if (!db.open())
  {
    return db.lastError();
  }
  QSqlQuery query;
  query.exec("CREATE TABLE customer("
             " code INT PRIMARY KEY,"  // NOT NULL,"  // AUTO_INCREMENT,"
             " name VARCHAR(100),"
             " address VARCHAR(100)"
             " )");
  query.exec("INSERT INTO customer (name, address) VALUES ('Paul', 'rue de Paris')");
  query.exec("INSERT INTO customer (name, address) VALUES ('Pierre', 'rue de la gare')");

  query.exec("CREATE TABLE item("
             " code INT PRIMARY KEY,"  // NOT NULL,"  // AUTO_INCREMENT,"
             " type VARCHAR(100),"
             " price INT"
             " )");
  query.exec("INSERT INTO item (type, price) VALUES ('Fruit', '5')");
  query.exec("INSERT INTO item (type, price) VALUES ('Vegetable', '6')");

  qDebug() << "List of tables:" <<Qt::endl;
  QStringList tablesList = db.tables();
  for (auto table : tablesList)
  {
    qDebug() << table << Qt::endl;
  }

  return db.lastError();
}

QSqlError initDb(QString databasepath)
{
  QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
  db.setDatabaseName(databasepath);

  if (!db.open())
  {
    return db.lastError();
  }

  QStringList tables = db.tables();
  if (tables.contains("customer", Qt::CaseInsensitive))
  {
    qDebug() << "Open table " << tables[0];
    return QSqlError();
  }

  return db.lastError();
}

#endif  // DATABASE_H
