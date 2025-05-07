// Copyright [2025] Auli Jussila & Mikko Memonen

#ifndef SEARCH_WINDOW_H
#define SEARCH_WINDOW_H

#include "item_info_window.h"
#include "mode_frame.h"
#include "search_model.h"
#include "search_proxy_model.h"
#include <QFormLayout>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QTableView>
#include <QComboBox>
#include <container_model.h>

class SearchWindow : public ModeFrame {
  Q_OBJECT;
  
 public:
  SearchWindow(ContainerModel *model, SearchModel *searchModel,
               SearchProxyModel *searchProxyModel, QWidget *parent = nullptr); 
  ~SearchWindow() override = default;
  void refresh();

 public slots:
  void handleRowSelection(const QModelIndex &current, const QModelIndex &);

 signals:
  void goToItemClicked(Item *item, Container *container);
  
 private:
  ContainerModel *model;
  SearchModel *searchModel;
  SearchProxyModel *searchProxyModel;
  ItemInfoWindow *infoWindow;
  QLabel *placeholder;
  QFrame *searchForm;
  QTableView *table;
  QLineEdit *nameFilter;
  QLineEdit *tagsFilter;
  QLineEdit *descriptionFilter;
  QComboBox *containersFilter;
  
  // Makes this concrete.
  virtual void dummyFunction() override {}
  void initSearchForm();
  void initTable();
  void initInfoWindow();
  void connectFilters();
  void updateContainerNames();
};

#endif // !SEARCH_WINDOW_H
