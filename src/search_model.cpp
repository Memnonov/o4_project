#include "../include/o4_project/search_model.h"
#include <qcontainerfwd.h>
#include <qlogging.h>
#include <qnamespace.h>

SearchModel::SearchModel(ContainerModel *model, QObject *parent)
    : QAbstractTableModel{parent}, model{model} {
  refresh();
}

// TODO: Implement these stubs.
int SearchModel::rowCount(const QModelIndex &parent) const {
  qDebug() << "rowCount called";
  return filteredItems.size();
}
int SearchModel::columnCount(const QModelIndex &parent) const {
  qDebug() << "columnCount called";
  return 5;
}

QVariant SearchModel::data(const QModelIndex &index, int role) const {
  qDebug() << "data called";
  if (!index.isValid() || role != Qt::DisplayRole) {
    qDebug() << "Invalid index or role in table model";
    if (role == Qt::TextAlignmentRole) {
      return Qt::AlignCenter;
    }
    return {};
  }
  qDebug() << "Getting data.";
  const auto &entry = filteredItems.at(index.row());
  switch (index.column()) {
  case 0:
    return entry.item->name;
  case 1:
    return entry.item->quantity;
  case 2:
    return entry.item->tags.join(", ");
  case 3:
    return entry.container->name;
  case 4:
    return entry.item->description;
  default:
    return {};
  }
}

QVariant SearchModel::headerData(int section, Qt::Orientation orientation,
                                 int role) const {
  if (role == Qt::DisplayRole) {
    if (orientation == Qt::Horizontal) {
      switch (section) {
      case 0:
        return "Name";
      case 1:
        return "Quantity";
      case 2:
        return "Tags";
      case 3:
        return "In Container";
      case 4:
        return "Description";
      default:
        return {};
      }
    }
  }
  return QVariant{};
}

QVector<SearchModel::ItemEntry> SearchModel::getItemsFromModel() {
  if (!model) {
    return {};
  }
  QVector<ItemEntry> entries;
  auto containers = model->getContainers();
  for (auto const &container : containers) {
    for (auto const &item : container->getItems()) {
      entries << ItemEntry{item, container.get()};
    }
  }
  qDebug() << "Entries for SearchModel, size: " << entries.size();
  return entries;
}

void SearchModel::refresh() {
  beginResetModel();
  filteredItems = getItemsFromModel(); // TODO: Implement filtering
  qDebug() << "Model contains entries: " << filteredItems.size();
  endResetModel();
}
