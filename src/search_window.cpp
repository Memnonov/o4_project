#include "../include/o4_project/search_window.h"
#include "main_window.h"
#include "search_proxy_model.h"
#include <QHeaderView>
#include <qabstractitemview.h>
#include <qheaderview.h>
#include <qnamespace.h>

SearchWindow::SearchWindow(ContainerModel *model, SearchModel *searchModel,
                           SearchProxyModel *searchProxyModel, QWidget *parent)
    : ModeFrame{parent}, model{model}, searchModel{searchModel},
      searchProxyModel{searchProxyModel}, infoWindow{new ItemInfoWindow},
      placeholder(new QLabel{"Search window here!"}), searchForm{new QFrame},
      table{new QTableView}, nameFilter{new QLineEdit},
      tagsFilter{new QLineEdit}, descriptionFilter{new QLineEdit},
      containersFilter{new QComboBox} {
  layout->setAlignment(Qt::AlignCenter);
  layout->addWidget(searchForm);
  layout->addWidget(table);
  layout->setStretch(0, 1);
  layout->setStretch(1, 2);

  initTable();
  initSearchForm();
  initInfoWindow();
}

void SearchWindow::initTable() {
  searchProxyModel->setSourceModel(searchModel);
  searchProxyModel->setSortCaseSensitivity(Qt::CaseInsensitive);

  table->setModel(searchProxyModel);
  table->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
  table->horizontalHeader()->setStretchLastSection(true);
  table->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
  table->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
  table->setSelectionBehavior(QAbstractItemView::SelectRows);
  table->setSelectionMode(QAbstractItemView::SingleSelection);
  table->horizontalHeader()->setSectionsMovable(true);

  table->setSortingEnabled(true);
  connect(table->selectionModel(), &QItemSelectionModel::currentRowChanged,
          this, &SearchWindow::handleRowSelection);
  connect(searchModel, &SearchModel::refreshProxy, searchProxyModel,
          &SearchProxyModel::refresh);

  table->show();
  connectFilters();
}

void SearchWindow::handleRowSelection(const QModelIndex &current,
                                      const QModelIndex &) {
  if (!current.isValid()) {
    return;
  }
  auto sourceIndex = searchProxyModel->mapToSource(current);
  auto entry = searchModel->entryAt(sourceIndex.row());
  infoWindow->handleItemSelected(entry.item.get(), entry.container.get());
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

  searchForm->layout()->addWidget(infoWindow);
}

void SearchWindow::initInfoWindow() {
  infoWindow->setEditable(false);
  infoWindow->setFavouritable(false);
  infoWindow->setGoToEnabled(true);
  connect(infoWindow, &ItemInfoWindow::goToItemClicked, this,
          &SearchWindow::goToItemClicked);
}

void SearchWindow::updateContainerNames() {
  containersFilter->clear();
  containersFilter->addItem("Any");
  containersFilter->addItems(model->getContainerNames());
}

void SearchWindow::refresh() {
  updateContainerNames();
  table->resizeRowsToContents();
  table->resizeColumnsToContents();
  infoWindow->handleItemSelected(); // Set to null in case of changes.
  searchModel->refresh();
}

void SearchWindow::connectFilters() {
  connect(nameFilter, &QLineEdit::textChanged, searchProxyModel,
          &SearchProxyModel::setNameFilter);
  connect(tagsFilter, &QLineEdit::textChanged, searchProxyModel,
          &SearchProxyModel::setTagsFilter);
  connect(descriptionFilter, &QLineEdit::textChanged, searchProxyModel,
          &SearchProxyModel::setDescriptionFilter);
  connect(containersFilter, &QComboBox::currentTextChanged, this,
          [this](const QString &text) {
            searchProxyModel->setContainerFilter(text == "Any" ? "" : text);
          });
}
