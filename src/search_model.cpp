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
  return items.size();
}
int SearchModel::columnCount(const QModelIndex &parent) const {
  return 5;
}

QVariant SearchModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid() || role != Qt::DisplayRole) {
    if (role == Qt::TextAlignmentRole) {
      return Qt::AlignCenter;
    }
    return {};
  }
  const auto &entry = items.at(index.row());
  switch (index.column()) {
    case NAME:
    return entry.item->name;
  case QUANTITY:
    return entry.item->quantity;
  case TAGS:
    return entry.item->tags.join(", ");
  case CONTAINER:
    return entry.container->name;
  case DESCRIPTION:
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
        return "#";
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
  return entries;
}

void SearchModel::refresh() {
  beginResetModel();
  // TODO: Filterint to be implemented in the proxy model?
  items = getItemsFromModel();
  endResetModel();
}

const SearchModel::ItemEntry &SearchModel::entryAt(int row) const {
  return items.at(row);
}
