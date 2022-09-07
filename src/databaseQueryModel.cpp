#include "databaseQueryModel.h"
#include <QDebug>
#include <QSqlRecord>

DatabaseQueryModel::DatabaseQueryModel(QObject *parent) : QSqlQueryModel(parent)
{
  qDebug() << "DatabaseQueryModel::DatabaseQueryModel(QObject *parent)" << Qt::endl;
}

void DatabaseQueryModel::refresh()
{
}

void DatabaseQueryModel::setQuery(const QString &query, const QSqlDatabase &db)
{
  QSqlQueryModel::setQuery(query, db);
  generateRoleNames();
}

Qt::ItemFlags DatabaseQueryModel::flags(const QModelIndex &index) const
{
  Qt::ItemFlags flags = QSqlQueryModel::flags(index);
  if (index.column() == 1 || index.column() == 2)
    flags |= Qt::ItemIsEditable;
  return flags;
}

QHash<int, QByteArray> DatabaseQueryModel::roleNames() const
{
  qDebug("QHash<int, QByteArray> DatabaseQueryModel::roleNames() const");
  return m_roleNames;
}

QVariant DatabaseQueryModel::data(const QModelIndex &index, int role) const
{
  qDebug("QVariant DatabaseQueryModel::data(const QModelIndex &index, int role) const");
  QVariant value;
  if (role < Qt::UserRole)
  {
    value = QSqlQueryModel::data(index, role);
  }
  else
  {
    int columnIdx = role - Qt::UserRole - 1;
    QModelIndex modelIndex = this->index(index.row(), columnIdx);
    value = QSqlQueryModel::data(modelIndex, Qt::DisplayRole);
  }
  return value;
}

bool DatabaseQueryModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
  return true;
}

void DatabaseQueryModel::generateRoleNames()
{
  m_roleNames.clear();
  for (int i = 0; i < record().count(); i++)
  {
    m_roleNames.insert(Qt::UserRole + i + 1, record().fieldName(i).toUtf8());
  }
}
