// Copyright [2025] Auli Jussila & Mikko Memonen

#ifndef SEARCH_PROXY_MODEL_H
#define SEARCH_PROXY_MODEL_H

#include <QSortFilterProxyModel>

class SearchProxyModel : public QSortFilterProxyModel {
  Q_OBJECT;
  
 public:
  SearchProxyModel(QObject *parent = nullptr) : QSortFilterProxyModel{parent} {
    resetFilters();
  }
  ~SearchProxyModel() = default;
  void refresh();

  void setNameFilter(const QString &nameFilter) {
    this->nameFilter = nameFilter;
    invalidateFilter();
  }

  void setTagsFilter(const QString &tagsFilter) {
    this->tagsFilter = tagsFilter;
    invalidateFilter();
  }

  void setContainerFilter(const QString &containerFilter) {
    this->containerFilter = containerFilter;
    invalidateFilter();
  }

  void setDescriptionFilter(const QString &descriptionFilter) {
    this->descriptionFilter = descriptionFilter;
    invalidateFilter();
  }

  void resetFilters();

 protected:
  bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;

 private:
  QString nameFilter;
  QString tagsFilter;
  QString containerFilter;
  QString descriptionFilter;
};

#endif // !SEARCH_PROXY_MODEL_H
