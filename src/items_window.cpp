
#include "../include/o4_project/items_window.h"
#include <QLabel>
#include <QPushButton>
#include <qboxlayout.h>
#include <qlogging.h>
#include <qmainwindow.h>
#include <qnamespace.h>
#include <qpushbutton.h>
#include <qsizepolicy.h>
#include <qwidget.h>
#include <QToolBar>

ItemsWindow::ItemsWindow(QWidget *parent)
    : QFrame{parent}, layout{new QVBoxLayout{this}},
      scrollArea{new QScrollArea{this}} {
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
  connect(closeButton, &QPushButton::clicked, this, &ItemsWindow::closeButtonPushed);
  QLabel *itemsLabel = new QLabel{"<b>Items</b>"};
  itemsLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  itemsLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
  topRow->addWidget(itemsLabel);
  topRow->addWidget(closeButton);
  // topRow->setLayout(topRowLayout);
  layout->addWidget(topRow);

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
}

void ItemsWindow::createDummyRows(QVBoxLayout *rows) {
  // Creating dummy rows
  rows->setSpacing(0);
  // TODO(mikko): Fix asset paths.
  QIcon deleteIcon{"./assets/icons/trash.svg"};
  if (deleteIcon.isNull()) {
    qDebug() << "Couldn't load icon\n";
  }
  for (unsigned int i = 0; i < 18; ++i) {
    QWidget *row = new QWidget;
    row->setMinimumHeight(40); // TODO(mikko): fix magic numbers
    QHBoxLayout *box = new QHBoxLayout;
    box->setContentsMargins(0, 0, 4, 4);
    box->setSpacing(0);

    QPushButton *button = new QPushButton{"Junk Button"};
    button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    connect(button, &QPushButton::clicked, this,
            [this]() { emit itemSelected(); });

    QPushButton *deleteButton = new QPushButton;
    deleteButton->setIcon(deleteIcon);
    deleteButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);

    row->setLayout(box);
    box->addWidget(button);
    box->addWidget(deleteButton);
    rows->addWidget(row);
  }
}
