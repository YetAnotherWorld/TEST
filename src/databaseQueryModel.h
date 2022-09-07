#ifndef CUSTOMERMODEL_H
#define CUSTOMERMODEL_H

#include <QDate>
#include <QSqlQueryModel>

// TODO: Cached table (read then submit change): https://doc.qt.io/qt-5/examples-sql.html
// TODO: Query model (1 DB several Table)
// TODO: Relational (Items share relation between table)

class DatabaseQueryModel : public QSqlQueryModel
{
  Q_OBJECT

public:
  explicit DatabaseQueryModel(QObject *parent = nullptr);
  void refresh();
  void setQuery(const QString &query, const QSqlDatabase &db = QSqlDatabase());

  Qt::ItemFlags flags(const QModelIndex &index) const override;
  QHash<int, QByteArray> roleNames() const override;
  QVariant data(const QModelIndex &index, int role) const override;
  //int rowCount(const QModelIndex &parent) const final;
  bool setData(const QModelIndex &index, const QVariant &value, int role) override;
  //  Q_INVOKABLE void sort(int column,Qt::SortOrder order=Qt::AscendingOrder) override;

private:
  void generateRoleNames();
  QHash<int, QByteArray> m_roleNames;
};

#endif  // CustomerModel_H
