#include "../include/o4_project/search_window.h"
#include <QHeaderView>
#include <qabstractitemview.h>
#include <qheaderview.h>
#include <qnamespace.h>

SearchWindow::SearchWindow(ContainerModel *model, SearchModel *searchModel,
                           QWidget *parent)
    : ModeFrame{parent}, model{model}, searchModel{searchModel},
      placeholder(new QLabel{"Search window here!"}), searchForm{new QFrame},
      table{new QTableView}, name{new QLineEdit}, tags{new QLineEdit},
      description{new QLineEdit}, containersBox{new QComboBox} {
  layout->setAlignment(Qt::AlignCenter);
  layout->addWidget(searchForm);
  layout->addWidget(table);
  layout->setStretch(0, 2);
  layout->setStretch(1, 4);

  initTable();
  initSearchForm();
}

void SearchWindow::initTable() {
  auto proxyModel = new QSortFilterProxyModel();
  proxyModel->setSourceModel(searchModel);
  proxyModel->setSortCaseSensitivity(Qt::CaseInsensitive);
  
  table->setModel(proxyModel);
  table->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
  table->horizontalHeader()->setStretchLastSection(true);
  table->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
  table->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
  table->setSelectionBehavior(QAbstractItemView::SelectRows);
  table->setSelectionMode(QAbstractItemView::SingleSelection);
  table->horizontalHeader()->setSectionsMovable(true);

  table->setSortingEnabled(true);
  
  table->show();
}

void SearchWindow::initSearchForm() {
  searchForm->setFrameShape(StyledPanel);
  auto vbox = new QVBoxLayout;
  searchForm->setLayout(vbox);
  vbox->setAlignment(Qt::AlignTop);

  vbox->addWidget(new QLabel{"<b>Search Items</b>"});
  vbox->addSpacing(10);
  vbox->addWidget(new QLabel{"Container:"});
  vbox->addWidget(containersBox), vbox->addWidget(new QLabel{"Item name:"});
  updateContainerNames();
  vbox->addWidget(name);
  vbox->addWidget(new QLabel{"Tags:"});
  vbox->addWidget(tags);
  vbox->addWidget(new QLabel{"Description:"});
  vbox->addWidget(description);
  vbox->addSpacing(10);
  auto tipBox = new QLabel{"<b>Help</b><br>Some help here."};

  tipBox->setAlignment(Qt::AlignCenter);

  searchForm->layout()->addWidget(tipBox);
}

void SearchWindow::updateContainerNames() {
  containersBox->clear();
  containersBox->addItem("Any");
  containersBox->addItems(model->getContainerNames());
}

void SearchWindow::refresh() {
  updateContainerNames();
  table->resizeRowsToContents();
  table->resizeColumnsToContents();
}
