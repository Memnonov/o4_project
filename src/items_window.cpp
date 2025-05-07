#include "../include/o4_project/items_window.h"
#include <QButtonGroup>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QToolBar>
#include <algorithm>
#include <qabstractbutton.h>
#include <qboxlayout.h>
#include <qcontainerfwd.h>
#include <qframe.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qlogging.h>
#include <qmainwindow.h>
#include <qnamespace.h>
#include <qpushbutton.h>
#include <qsizepolicy.h>
#include <qtmetamacros.h>
#include <qtoolbar.h>
#include <qwidget.h>

ItemsWindow::ItemsWindow(QWidget *parent)
    : QFrame{parent}, layout{new QVBoxLayout{this}}, title{new QLabel},
      addDeleteWidget{new QWidget}, scrollArea{new QScrollArea{this}},
      selectedItemButton{nullptr}, filterSortPanel{new QToolBar},
      editButton{new QPushButton}, sortMode{ItemsWindow::SortMode::AtoZ},
      itemRows{new QVBoxLayout}, moveItemsButton{new QPushButton},
      editNameLine{new QLineEdit} {
  setFrameShape(StyledPanel);
  setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

  // Setting up the top row
  auto topRow = new QWidget;
  auto topRowLayout = new QHBoxLayout{topRow};

  closeButton = new QPushButton;
  auto closeIcon = QIcon{":/icons/xmark.svg"};
  if (closeIcon.isNull()) {
    qDebug() << "Couldn't load close button icon";
  }
  closeButton->setIcon(closeIcon);
  closeButton->setFlat(true);
  connect(closeButton, &QPushButton::clicked, this,
          &ItemsWindow::closeButtonPushed);
  title->setText("No container selected");
  title->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  title->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

  editNameLine->setPlaceholderText("Container Name");
  initEditButton();

  topRowLayout->addWidget(title);
  topRowLayout->addWidget(editNameLine);
  topRowLayout->addWidget(editButton);
  topRowLayout->addWidget(closeButton);
  // topRow->setLayout(topRowLayout);
  layout->addWidget(topRow);
  editNameLine->setVisible(false);
  topRow->update();

  // Set up filterSortPanel
  filterSortPanel->addWidget(new QLabel{"Filter: "});
  auto filterInput = new QLineEdit{};
  filterInput->setPlaceholderText("Write item name or #tag here");
  filterSortPanel->addWidget(filterInput);
  auto sortButton = new QPushButton{sortModeToString.value(sortMode)};
  connect(sortButton, &QPushButton::clicked, this, [this, sortButton]() {
    sortButton->setText(cycleSortMode());
    updateRows();
    qDebug() << "Changed sort mode!";
  });
  filterSortPanel->addWidget(sortButton);
  layout->addWidget(filterSortPanel);

  // Set up item rows.
  auto rowsWidget = new QWidget;
  updateRows();
  rowsWidget->setLayout(itemRows);
  itemRows->setAlignment(Qt::AlignTop);
  scrollArea->setWidgetResizable(true);
  scrollArea->setWidget(rowsWidget);
  scrollArea->setAlignment(Qt::AlignTop);
  layout->addWidget(scrollArea);

  auto moveWidget = new QWidget;
  auto moveBox = new QHBoxLayout;
  moveWidget->setLayout(moveBox);
  moveBox->addWidget(moveItemsButton);
  moveItemsButton->setVisible(false);
  moveItemsButton->setIcon(QIcon(":/icons/arrow-separate"));
  moveItemsButton->setText("Move items");
  layout->addWidget(moveWidget);

  // auto bottomRow = new QWidget;
  auto bottomRowLayout = new QHBoxLayout;
  addDeleteWidget->setLayout(bottomRowLayout);
  auto bottomAddButton = new QPushButton{"Add"};
  bottomAddButton->setIcon(QIcon(":/icons/plus.svg"));
  bottomRowLayout->addWidget(bottomAddButton);
  bottomDeleteButton = new QPushButton{"Delete"};
  bottomDeleteButton->setEnabled(false);
  QIcon deleteIcon{":/icons/trash.svg"};
  if (deleteIcon.isNull()) {
    qDebug() << "Couldn't load icon\n";
  }
  bottomDeleteButton->setIcon(deleteIcon);
  bottomRowLayout->addWidget(bottomDeleteButton);
  layout->addWidget(addDeleteWidget);
  connect(bottomDeleteButton, &QPushButton::clicked, this,
          [this]() { confirmDeleteItem(); });
}

Container *ItemsWindow::getCurrentContainer() {
  return currentContainer;
}

void ItemsWindow::selectItem(Item* item) {
  for (auto &button : buttonGroup->buttons()) {
    if (item == button->property("item").value<Item*>()) {
      button->setChecked(true);
    }
  }
}

void ItemsWindow::initEditButton() {
  editButton->setIcon(QIcon(":/icons/edit-pencil.svg"));
  editButton->setFlat(true);
  connect(editButton, &QPushButton::clicked, this,
          [this]() { toggleEditing(); });
}

void ItemsWindow::refresh() {
  updateRows();
}

void ItemsWindow::toggleEditing() {
  editing = !editing;
  title->setVisible(!editing);
  editNameLine->setVisible(editing);
}

void ItemsWindow::createDummyRows(QVBoxLayout *rows) {
  // Creating dummy rows
  rows->setSpacing(0);
  buttonGroup = new QButtonGroup{this};
  buttonGroup->setExclusive(!movingItems);
  // TODO(mikko): Fix asset paths.
  if (!currentContainer) {
    return;
  }
  static constexpr unsigned int minHeight = 40;
  static constexpr unsigned int maxHeight = minHeight * 2;

  auto items = currentContainer->getItems();
  std::sort(items.begin(), items.end(), ItemsWindow::comparators.at(sortMode));

  for (auto const &item : items) {
    QPushButton *moveButton;

    if (movingItems) {
      moveButton = new QPushButton;
      moveButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    }

    QWidget *row = new QWidget;
    row->setMinimumHeight(minHeight); // TODO(mikko): fix magic numbers?
    row->setMaximumHeight(maxHeight);
    QHBoxLayout *box = new QHBoxLayout;
    box->setContentsMargins(0, 0, 4, 4);
    box->setSpacing(0);

    QPushButton *button =
        new QPushButton{QString("%1 × %2").arg(item->name).arg(item->quantity)};
    button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    button->setCheckable(true);
    button->setProperty("item", QVariant::fromValue(item));
    buttonGroup->addButton(button);
    if (item->favourite) {
      button->setIcon(QIcon{":/icons/star-solid.svg"});
    }

    connect(button, &QPushButton::clicked, this, [this, item, button]() {
      emit itemSelected(item, currentContainer);
      qDebug() << "Clicked on item: "
               << button->property("item").value<Item *>()->name;
      bottomDeleteButton->setEnabled(true);
    });

    row->setLayout(box);
    if (movingItems && isRightWindow) {
      box->addWidget(moveButton);
      moveButton->setIcon(QIcon(":/icons/fast-arrow-left"));
    }
    box->addWidget(button);
    rows->addWidget(row);

    if (!movingItems) {
      QIcon plusIcon{":/icons/plus-noborder.svg"};
      QIcon minusIcon{":/icons/minus.svg"};
      QPushButton *plusButton = new QPushButton;
      plusButton->setIcon(plusIcon);
      plusButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
      QPushButton *minusButton = new QPushButton;
      minusButton->setIcon(minusIcon);
      minusButton->setSizePolicy(QSizePolicy::Preferred,
                                 QSizePolicy::Expanding);
      box->addWidget(minusButton);
      box->addWidget(plusButton);
    } else if (!isRightWindow) {
      box->addWidget(moveButton);
      moveButton->setIcon(QIcon(":/icons/fast-arrow-right"));
    }
  }
}

void ItemsWindow::updateRows() {
  if (itemRows->count() > 0) {
    QLayoutItem *item;
    while ((item = itemRows->takeAt(0)) != nullptr) {
      item->widget()->deleteLater();
    }
  }
  createDummyRows(itemRows);
  // New item button.
  QPushButton *newButton = new QPushButton{"Add New"};
  QIcon plusIcon{":/icons/plus.svg"};
  newButton->setIcon(plusIcon);
  newButton->setFlat(true), newButton->setMinimumHeight(40);
  newButton->setMinimumHeight(40);
  itemRows->addWidget(newButton);
}

// Kinda hacky!?
void ItemsWindow::closeButtonPushed() {
  buttonGroup->setExclusive(false);
  bottomDeleteButton->setEnabled(false);
  auto checked = buttonGroup->checkedButton();
  if (checked) {
    qDebug() << "Should have unchecked a button?";
    checked->setChecked(false);
  }
  buttonGroup->setExclusive(true);
  currentContainer = nullptr;
  emit itemsWindowClosed();
}

QString ItemsWindow::cycleSortMode() {
  unsigned int currentMode = static_cast<unsigned int>(sortMode);
  currentMode = (++currentMode) % sortModeToString.count();
  sortMode = static_cast<ItemsWindow::SortMode>(currentMode);
  return sortModeToString.value(sortMode, "");
}

QVector<Item *> ItemsWindow::getSelectedItems() const {
  QVector<Item *> items;
  for (auto button : buttonGroup->buttons()) {
    if (button->isChecked()) {
      items.push_back(button->property("item").value<Item *>());
    }
  }
  return items;
}

void ItemsWindow::handleContainerSelected(Container *container) {
  if (!container) {
    return;
  }
  currentContainer = container;
  title->setText(
      QString("<b>%1</b>").arg((container) ? container->name : "null"));
  editNameLine->setText(container->name);
  updateRows();
}

bool ItemsWindow::hasItemSelected() const {
  for (auto button : buttonGroup->buttons()) {
    if (button->isChecked()) {
      return true;
    }
  }
  return false;
}

void ItemsWindow::setCanMoveItems(bool canMove) {
  moveItemsButton->setEnabled(canMove);
}

void ItemsWindow::confirmDeleteItem() {
  QMessageBox messageBox{this};
  messageBox.setIcon(QMessageBox::Icon::Warning);

  auto items = getSelectedItems();
  QStringList itemsString;
  std::for_each(items.begin(), items.end(), [&itemsString](Item *item) {
    itemsString.push_back(item->name);
  });

  messageBox.setText(
      QString{"Delete items:<br>%1"}.arg(itemsString.join(", ")));
  messageBox.setDefaultButton(QMessageBox::Cancel);
  messageBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
  auto choice = messageBox.exec();
}

// Looks very ugly, but no time to fight the autoformat ; )
const std::unordered_map<ItemsWindow::SortMode,
                         std::function<bool(const Item *, const Item *)>>
    ItemsWindow::comparators = {

        {ItemsWindow::SortMode::AtoZ,
         [](const Item *a, const Item *b) {
           if (a->favourite != b->favourite) {
             return a->favourite;
           }
           return a->name < b->name;
         }},

        {ItemsWindow::SortMode::ZtoA,
         [](const Item *a, const Item *b) {
           if (a->favourite != b->favourite) {
             return a->favourite;
           }
           return a->name > b->name;
         }},

        {ItemsWindow::SortMode::Quantity,
         [](const Item *a, const Item *b) {
           if (a->favourite != b->favourite) {
             return a->favourite;
           }
           return a->quantity > b->quantity;
         }}

};
