#include "../include/o4_project/search_window.h"
#include "search_proxy_model.h"
#include <QHeaderView>
#include <qabstractitemview.h>
#include <qheaderview.h>
#include <qnamespace.h>

SearchWindow::SearchWindow(ContainerModel *model, SearchModel *searchModel,
                           SearchProxyModel *searchProxyModel, QWidget *parent)
    : ModeFrame{parent}, model{model}, searchModel{searchModel},
      searchProxyModel{searchProxyModel},
      placeholder(new QLabel{"Search window here!"}), searchForm{new QFrame},
      tableFilter{new QTableView}, nameFilter{new QLineEdit},
      tagsFilter{new QLineEdit}, descriptionFilter{new QLineEdit},
      containersFilter{new QComboBox} {
  layout->setAlignment(Qt::AlignCenter);
  layout->addWidget(searchForm);
  layout->addWidget(tableFilter);
  layout->setStretch(0, 2);
  layout->setStretch(1, 4);

  initTable();
  initSearchForm();
}

void SearchWindow::initTable() {
  searchProxyModel->setSourceModel(searchModel);
  searchProxyModel->setSortCaseSensitivity(Qt::CaseInsensitive);

  tableFilter->setModel(searchProxyModel);
  tableFilter->horizontalHeader()->setSectionResizeMode(
      QHeaderView::Interactive);
  tableFilter->horizontalHeader()->setStretchLastSection(true);
  tableFilter->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
  tableFilter->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
  tableFilter->setSelectionBehavior(QAbstractItemView::SelectRows);
  tableFilter->setSelectionMode(QAbstractItemView::SingleSelection);
  tableFilter->horizontalHeader()->setSectionsMovable(true);

  tableFilter->setSortingEnabled(true);

  tableFilter->show();
  connectFilters();
}

void SearchWindow::initSearchForm() {
  searchForm->setFrameShape(StyledPanel);
  auto vbox = new QVBoxLayout;
  searchForm->setLayout(vbox);
  vbox->setAlignment(Qt::AlignTop);

  nameFilter->setPlaceholderText("e.g. sword, iron rations");
  tagsFilter->setPlaceholderText("e.g. weapon, healing");
  descriptionFilter->setPlaceholderText("e.g. damage +1, cursed");

  vbox->addWidget(new QLabel{"<b>Search Items</b>"});
  vbox->addSpacing(10);
  vbox->addWidget(new QLabel{"Container:"});
  vbox->addWidget(containersFilter), vbox->addWidget(new QLabel{"Item name:"});
  updateContainerNames();
  vbox->addWidget(nameFilter);
  vbox->addWidget(new QLabel{"Tag:"});
  vbox->addWidget(tagsFilter);
  vbox->addWidget(new QLabel{"Description:"});
  vbox->addWidget(descriptionFilter);
  vbox->addSpacing(10);
  auto tipBox = new QLabel{"<b>Help</b><br>Some help here."};

  tipBox->setAlignment(Qt::AlignCenter);

  searchForm->layout()->addWidget(tipBox);
}

void SearchWindow::updateContainerNames() {
  containersFilter->clear();
  containersFilter->addItem("Any");
  containersFilter->addItems(model->getContainerNames());
}

void SearchWindow::refresh() {
  updateContainerNames();
  tableFilter->resizeRowsToContents();
  tableFilter->resizeColumnsToContents();
}

void SearchWindow::connectFilters() {
  connect(nameFilter, &QLineEdit::textChanged, searchProxyModel,
          &SearchProxyModel::setNameFilter);
  connect(tagsFilter, &QLineEdit::textChanged, searchProxyModel,
          &SearchProxyModel::setTagsFilter);
  connect(descriptionFilter, &QLineEdit::textChanged, searchProxyModel,
          &SearchProxyModel::setDescriptionFilter);
  connect(containersFilter, &QComboBox::currentTextChanged, this, [this] (const QString &text) {

    searchProxyModel->setContainerFilter(text == "Any" ? "" : text);
  });
}
