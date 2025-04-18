#include "../include/o4_project/items_window.h"
#include <QButtonGroup>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QToolBar>
#include <qabstractbutton.h>
#include <qboxlayout.h>
#include <qlineedit.h>
#include <qlogging.h>
#include <qmainwindow.h>
#include <qnamespace.h>
#include <qpushbutton.h>
#include <qsizepolicy.h>
#include <qtoolbar.h>
#include <qwidget.h>

ItemsWindow::ItemsWindow(QWidget *parent)
    : QFrame{parent}, layout{new QVBoxLayout{this}},
      scrollArea{new QScrollArea{this}}, selectedItemButton{nullptr}, filterSortPanel{new QToolBar}, sortMode{ItemsWindow::SortMode::AtoZ} {
  setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

  // Setting up the top row
  auto topRow = new QToolBar;
  // auto topRowLayout = new QHBoxLayout;
  closeButton = new QPushButton;
  auto closeIcon = QIcon{"./assets/icons/xmark.svg"};
  if (closeIcon.isNull()) {
    qDebug() << "Couldn't load close button icon";
  }
  closeButton->setIcon(closeIcon);
  closeButton->setFlat(true);
  connect(closeButton, &QPushButton::clicked, this,
          &ItemsWindow::closeButtonPushed);
  QLabel *itemsLabel = new QLabel{"<b>Items</b>"};
  itemsLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  itemsLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
  topRow->addWidget(itemsLabel);
  topRow->addWidget(closeButton);
  // topRow->setLayout(topRowLayout);
  layout->addWidget(topRow);

  // Set up filterSortPanel
  filterSortPanel->addWidget(new QLabel{"Filter: "});
  auto filterInput = new QLineEdit{};
  filterInput->setPlaceholderText("Write item name or #tag here");
  filterSortPanel->addWidget(filterInput);
  auto sortButton = new QPushButton{sortModeToString.value(sortMode)};
  connect(sortButton, &QPushButton::clicked, this, [this, sortButton]() {
    sortButton->setText(cycleSortMode());
    qDebug() << "Changed sort mode!";
  });
  filterSortPanel->addWidget(sortButton);
  layout->addWidget(filterSortPanel);

  // Set up item rows.
  QWidget *rowsWidget = new QWidget;
  QVBoxLayout *rows = new QVBoxLayout{rowsWidget};
  createDummyRows(rows);
  // New container button.
  QPushButton *newButton = new QPushButton{"Add New"};
  QIcon plusIcon{"./assets/icons/plus.svg"};
  newButton->setIcon(plusIcon);
  newButton->setMinimumHeight(40);
  rows->addWidget(newButton);

  scrollArea->setWidgetResizable(true);
  scrollArea->setWidget(rowsWidget);
  layout->addWidget(scrollArea);

  auto bottomRow = new QWidget;
  auto bottomRowLayout = new QHBoxLayout;
  bottomRow->setLayout(bottomRowLayout);
  auto bottomAddButton = new QPushButton{"Add"};
  bottomAddButton->setIcon(plusIcon);
  bottomRowLayout->addWidget(bottomAddButton);
  bottomDeleteButton = new QPushButton{"Delete"};
  bottomDeleteButton->setEnabled(false);
  QIcon deleteIcon{"./assets/icons/trash.svg"};
  if (deleteIcon.isNull()) {
    qDebug() << "Couldn't load icon\n";
  }
  bottomDeleteButton->setIcon(deleteIcon);
  bottomRowLayout->addWidget(bottomDeleteButton);
  newButton->setMinimumHeight(40);
  layout->addWidget(bottomRow);
}

void ItemsWindow::createDummyRows(QVBoxLayout *rows) {
  // Creating dummy rows
  rows->setSpacing(0);
  auto buttonGroup = new QButtonGroup;
  buttonGroup->setExclusive(true);
  // TODO(mikko): Fix asset paths.
  QIcon deleteIcon{"./assets/icons/trash.svg"};
  if (deleteIcon.isNull()) {
    qDebug() << "Couldn't load icon\n";
  }
  for (unsigned int i = 0; i < 18; ++i) {
    QWidget *row = new QWidget;
    row->setMinimumHeight(40); // TODO(mikko): fix magic numbers?
    QHBoxLayout *box = new QHBoxLayout;
    box->setContentsMargins(0, 0, 4, 4);
    box->setSpacing(0);

    QPushButton *button = new QPushButton{"Junk Button"};
    button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    button->setCheckable(true);
    buttonGroup->addButton(button);
    connect(button, &QPushButton::clicked, this, [this]() {
      emit itemSelected();
      bottomDeleteButton->setEnabled(true);
    });

    QPushButton *deleteButton = new QPushButton;
    deleteButton->setIcon(deleteIcon);
    deleteButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);

    row->setLayout(box);
    box->addWidget(button);
    box->addWidget(deleteButton);
    rows->addWidget(row);
  }
}

QString ItemsWindow::cycleSortMode() {
  unsigned int currentMode = static_cast<unsigned int>(sortMode);
  currentMode = (++currentMode) % sortModeToString.count();
  sortMode = static_cast<ItemsWindow::SortMode>(currentMode);
  return sortModeToString.value(sortMode, "");
}
