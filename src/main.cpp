/*
    SPDX-License-Identifier: GPL-2.0-or-later
    SPDX-FileCopyrightText: 2022 test <>
*/

#include <QApplication>
#include <QDebug>
#include <QQmlApplicationEngine>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlError>
#include <QUrl>
#include <QtQml>
 #include <QStandardPaths>

#include "database.h"
#include "databaseQueryModel.h"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
  QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  QApplication app(argc, argv);
  QCoreApplication::setApplicationName(QStringLiteral("test_talbe_sql"));

  QQmlApplicationEngine engine;

  qDebug() << createDb(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/database.db").text();

  DatabaseQueryModel *databasequerymodel = new DatabaseQueryModel(qApp);
  databasequerymodel->setQuery("SELECT * FROM customer");
  qmlRegisterUncreatableType<DatabaseQueryModel>(
    "org.kde.test_talbe_sql", 1, 0, "DatabaseQueryModel", QStringLiteral("Must be created from C++")
  );
  engine.setInitialProperties({{"databaseQueryModel", QVariant::fromValue(databasequerymodel)}});

  engine.load(QUrl(QStringLiteral("qrc:///main.qml")));

  if (engine.rootObjects().isEmpty())
  {
    return -1;
  }

  return app.exec();
}
