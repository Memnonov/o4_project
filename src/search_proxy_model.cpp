// Copyright [2025] Auli Jussila & Mikko Memonen

#include "../include/o4_project/search_proxy_model.h"
#include "search_model.h"
#include <qlogging.h>
#include <qnamespace.h>

void SearchProxyModel::resetFilters() {
  nameFilter = "";
  tagsFilter = "";
  containerFilter = "";
  descriptionFilter = "";
  invalidateFilter();
}

bool SearchProxyModel::filterAcceptsRow(int sourceRow,
                                        const QModelIndex &sourceParent) const {
  auto nameIndex =
      sourceModel()->index(sourceRow, SearchModel::NAME, sourceParent);
  auto tagsIndex =
      sourceModel()->index(sourceRow, SearchModel::TAGS, sourceParent);
  auto containerIndex =
      sourceModel()->index(sourceRow, SearchModel::CONTAINER, sourceParent);
  auto descriptionIndex =
      sourceModel()->index(sourceRow, SearchModel::DESCRIPTION, sourceParent);

  auto name = sourceModel()->data(nameIndex).toString();
  auto tags = sourceModel()->data(tagsIndex).toString();
  auto container = sourceModel()->data(containerIndex).toString();
  auto description = sourceModel()->data(descriptionIndex).toString();

  return name.contains(nameFilter, Qt::CaseInsensitive) &&
         tags.contains(tagsFilter, Qt::CaseInsensitive) &&
         container.contains(containerFilter, Qt::CaseInsensitive) &&
         description.contains(descriptionFilter, Qt::CaseInsensitive);
}

void SearchProxyModel::refresh() {
  invalidate();
}

