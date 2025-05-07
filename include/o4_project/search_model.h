#ifndef SEARCH_MODEL_H
#define SEARCH_MODEL_H

#include "container_model.h"
#include <QAbstractTableModel>
#include <QSortFilterProxyModel>

class SearchModel : public QAbstractTableModel {
  Q_OBJECT;

 public:
  SearchModel(ContainerModel *model, QObject *parent = nullptr);
  ~SearchModel() = default;

  enum Columns {
    NAME = 0,
    QUANTITY,
    TAGS,
    CONTAINER,
    DESCRIPTION,
  };
  
  void refresh();
  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  int columnCount(const QModelIndex &parent = QModelIndex()) const override;
  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
  QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
  
 private:
  ContainerModel *model;

  struct ItemEntry {
    Item *item;
    Container *container;
  };

  QVector<ItemEntry> items;
  QVector<ItemEntry> getItemsFromModel();
};

#endif // !SEARCH_MODEL_H
