// Copyright [2025] Auli Jussila & Mikko Memonen

#ifndef SEARCH_WINDOW_H
#define SEARCH_WINDOW_H

#include "mode_frame.h"
#include <QFormLayout>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QTableView>
#include <QComboBox>
#include <container_model.h>

class SearchWindow : public ModeFrame {
 public:
  SearchWindow(ContainerModel *model, QWidget *parent = nullptr); 
  ~SearchWindow() override = default;
  void refresh();

 private:
  ContainerModel *model;
  QLabel *placeholder;
  QFrame *searchForm;
  QTableView *table;
  QLineEdit *name;
  QLineEdit *tags;
  QLineEdit *description;
  QComboBox *containersBox;
  
  // Makes this concrete.
  virtual void dummyFunction() override {}
  void initSearchForm();
  void updateContainerNames();
};

#endif // !SEARCH_WINDOW_H
