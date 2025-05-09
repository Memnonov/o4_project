#include "../include/o4_project/search_model.h"
#include <qcontainerfwd.h>
#include <qlogging.h>
#include <qnamespace.h>
#include <strings.h>

SearchModel::SearchModel(ContainerModel *model, QObject *parent)
    : QAbstractTableModel{parent}, model{model} {
  setObjectName("SearchModel");
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
      return Qt::AlignLeft;
    }
    return {};
  }
  const auto &entry = items.at(index.row());
  if (!entry.item || !entry.container) {
    return {};
  }
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
  QVector<ItemEntry> entries;
  auto containers = model->getContainers();
  for (auto const &container : containers) {
    for (auto const &item : container->getItemRefs()) {
      entries << ItemEntry{item, container};
    }
  }
  return entries;
}

void SearchModel::refresh() {
  beginResetModel();
  items = getItemsFromModel();
  endResetModel();
  emit refreshProxy();
}

const SearchModel::ItemEntry &SearchModel::entryAt(int row) const {
  return items.at(row);
}
