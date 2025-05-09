#include "../include/o4_project/items_window.h"
#include <QButtonGroup>
#include <QInputDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QToolBar>
#include <algorithm>
#include <qbuttongroup.h>
#include <qlogging.h>
#include <qmessagebox.h>
#include <qnamespace.h>
#include <qobjectcleanuphandler.h>
#include <qpushbutton.h>
#include <qtmetamacros.h>
#include <qvector.h>
#include <strings.h>

ItemsWindow::ItemsWindow(QWidget *parent)
    : QFrame{parent}, layout{new QVBoxLayout{this}}, title{new QLabel{this}},
      addDeleteWidget{new QWidget}, scrollArea{new QScrollArea{this}},
      selectedItemButton{nullptr}, filterSortPanel{new QToolBar},
      buttonGroup{new QButtonGroup{this}}, editButton{new QPushButton},
      sortMode{ItemsWindow::SortMode::AtoZ}, itemRows{new QVBoxLayout},
      moveItemsButton{new QPushButton}, editNameLine{new QLineEdit},
      rowsCleaner(new QObjectCleanupHandler) {
  setObjectName("ItemsWindow");
  itemRows->setObjectName("ItemRows");
  itemRows->setSpacing(0);
  rowsCleaner->setParent(this);
  setFrameShape(StyledPanel);
  setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

  initFilterSortPanel();
  layout->addWidget(filterSortPanel);
  initTopRow();

  // Set up item rows.
  auto rowsWidget = new QWidget{this};
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
  connect(moveItemsButton, &QPushButton::clicked, this,
          [this]() { emit moveItemsClicked(getSelectedItems()); });
  layout->addWidget(moveWidget);

  // auto bottomRow = new QWidget;
  auto bottomRowLayout = new QHBoxLayout;
  addDeleteWidget->setLayout(bottomRowLayout);
  auto bottomAddButton = new QPushButton{"Add"};
  bottomAddButton->setIcon(QIcon(":/icons/plus.svg"));
  connect(bottomAddButton, &QPushButton::clicked, this,
          &ItemsWindow::handleAddNewClicked);

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

  dumpParents();
}

void ItemsWindow::initFilterSortPanel() {
  filterSortPanel->addWidget(new QLabel{"Filter: "});
  filterInput = new QLineEdit{filterSortPanel};
  filterInput->setPlaceholderText("Filter by item name, tag or decription");
  filterSortPanel->addWidget(filterInput);
  auto sortButton =
      new QPushButton{sortModeToString.value(sortMode), filterSortPanel};
  connect(sortButton, &QPushButton::clicked, this, [this, sortButton]() {
    sortButton->setText(cycleSortMode());
    updateRows();
  });
  filterSortPanel->addWidget(sortButton);
  connect(filterInput, &QLineEdit::textChanged, this, &ItemsWindow::refresh);
}

Container *ItemsWindow::getCurrentContainer() { return currentContainer; }

void ItemsWindow::selectItem(Item *item) {
  for (auto &button : buttonGroup->buttons()) {
    if (item == button->property("item").value<Item *>()) {
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

void ItemsWindow::refresh() { updateRows(); }

void ItemsWindow::toggleEditing() {
  editing = !editing;
  title->setVisible(!editing);
  editNameLine->setVisible(editing);
}

void ItemsWindow::createRows() {
  // TODO(mikko): maybe fix magic numbers?
  static constexpr unsigned int minHeight = 40;
  static constexpr unsigned int maxHeight = minHeight * 2;

  if (!currentContainer) {
    return;
  }

  buttonGroup->setExclusive(!movingItems);

  for (auto const &item : getSortedFilteredItems()) {
    QWidget *row = new QWidget;
    QPushButton *button = createItemButton(item);
    QHBoxLayout *box = new QHBoxLayout;
    QPushButton *moveButton;
    if (movingItems) {
      moveButton = new QPushButton;
      moveButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
      connect(moveButton, &QPushButton::clicked, this,
              [this, item] { emit moveItemClicked(item); });
    }

    // A holding box layout for the row
    box->setContentsMargins(0, 0, 4, 4);
    box->setSpacing(0);
    row->setLayout(box);
    row->setMinimumHeight(minHeight);
    row->setMaximumHeight(maxHeight);

    // if (movingItems && isRightWindow) {
    //   box->addWidget(moveButton);
    //   moveButton->setIcon(QIcon(":/icons/fast-arrow-left"));
    // }
    
    box->addWidget(button);
    itemRows->addWidget(row);

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
      connect(plusButton, &QPushButton::clicked, this, [this, item]() {
        emit setQuantityClicked(item, ++(item->quantity));
      });
      connect(minusButton, &QPushButton::clicked, this, [this, item]() {
        emit setQuantityClicked(item,
                                item->quantity == 0 ? 0 : --(item->quantity));
      });

    } else {
      auto icon = isRightWindow ? "./icons/fast-arrow-left" : "./icons/fast-arrow-right";
      unsigned int index = isRightWindow ? 0 : box->count();
      moveButton->setIcon(QIcon(icon));
      box->insertWidget(index, moveButton);
    }
    qDebug() << "Parent of row: " << row->parent();
    qDebug() << "Parent of button: " << button->parent();
    qDebug() << "Parent of itemRows: " << itemRows->parent();
    qDebug() << "Parent of box: " << box->parent();
    if (moveButton) {
      qDebug() << "Parent of moveButton: " << itemRows->parent();
    }
  }
}

QPushButton *ItemsWindow::createItemButton(Item *item) {
  auto button =
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
    bottomDeleteButton->setEnabled(true);
    currentItem = button->property("item").value<Item *>();
  });
  return button;
}

QVector<Item *> ItemsWindow::getSortedFilteredItems() {
  // Get sorted and filtered items
  auto items = currentContainer->getItems();
  std::sort(items.begin(), items.end(), ItemsWindow::comparators.at(sortMode));
  auto it = new QMutableVectorIterator<Item *>(items);
  while (it->hasNext()) {
    if (!filterItem(it->next())) {
      it->remove();
    }
  }
  return items;
}

bool ItemsWindow::filterItem(Item *item) {
  if (!item) {
    return false;
  }
  return item->name.contains(filterInput->text(), Qt::CaseInsensitive) ||
         item->tags.join(" ").contains(filterInput->text(),
                                       Qt::CaseInsensitive) ||
         item->description.contains(filterInput->text(), Qt::CaseInsensitive);
}

void ItemsWindow::updateRows() {
  // if (itemRows->count() > 0) {
  //   QLayoutItem *item;
  //   while ((item = itemRows->takeAt(0)) != nullptr) {
  //     item->widget()->deleteLater();
  //     delete item;
  //   }
  // }
  // if (buttonGroup) {
  //   for (auto button : buttonGroup->buttons()) {
  //     buttonGroup->removeButton(button);
  //     button->deleteLater();
  //   }
  // }

  createRows();
  if (!movingItems) { // No use keeping selection when moving stuff.
    selectItem(currentItem);
  }

  // New item button. Also dumb to remake it like this. No time to fix...
  if (newButton) {
    newButton->disconnect(newButton, &QPushButton::clicked, this,
                          &ItemsWindow::handleAddNewClicked);
  };
  newButton = new QPushButton{"Add New", this};
  QIcon plusIcon{":/icons/plus.svg"};
  newButton->setIcon(plusIcon);
  newButton->setFlat(true);
  newButton->setMinimumHeight(40);
  itemRows->addWidget(newButton);
  connect(newButton, &QPushButton::clicked, this,
          &ItemsWindow::handleAddNewClicked);
  qDebug() << "After update";
  dumpParents();
}

// Kinda hacky!?
void ItemsWindow::closeButtonPushed() {
  buttonGroup->setExclusive(false);
  bottomDeleteButton->setEnabled(false);
  auto checked = buttonGroup->checkedButton();
  if (checked) {
    checked->setChecked(false);
  }
  buttonGroup->setExclusive(true);
  currentContainer = nullptr;
  filterInput->clear();
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
  if (!buttonGroup) {
    return {};
  }
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
  filterInput->clear();
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

  auto item = getSelectedItems().at(0);

  messageBox.setText(QString{"Delete items:<br>%1"}.arg(item->name));
  messageBox.setDefaultButton(QMessageBox::Cancel);
  messageBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
  auto choice = messageBox.exec();
  if (choice == QMessageBox::Yes) {
    emit deleteItemClicked(item, currentContainer);
  }
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

void ItemsWindow::initTopRow() {
  auto topRow = new QWidget{this};
  auto topRowLayout = new QHBoxLayout{topRow};

  closeButton = new QPushButton{topRow};
  static const auto closeIcon = QIcon{":/icons/xmark.svg"};
  if (closeIcon.isNull()) {
    qDebug() << "Couldn't load close button icon";
  }
  closeButton->setIcon(closeIcon);
  closeButton->setFlat(true);
  title->setText("No container selected");
  title->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  title->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

  editNameLine->setPlaceholderText("Container Name");
  initEditButton();

  topRowLayout->addWidget(title);
  topRowLayout->addWidget(editNameLine);
  topRowLayout->addWidget(editButton);
  topRowLayout->addWidget(closeButton);
  layout->addWidget(topRow);
  editNameLine->setVisible(false);

  connect(closeButton, &QPushButton::clicked, this,
          &ItemsWindow::closeButtonPushed);

  topRow->update();
}

void ItemsWindow::handleAddNewClicked() {
  bool ok = false;
  auto name = QInputDialog::getText(
      this, "New Item", "Enter Item name:", QLineEdit::Normal, "", &ok);
  if (ok) {
    emit addNewClicked(currentContainer, name);
  }
}

void ItemsWindow::dumpParents() {
  qDebug() << "\n---------Dumping objects and parents of "
           << this->objectName();
  QVector<QObject *> objects = {
      title,           addDeleteWidget, scrollArea, selectedItemButton,
      filterSortPanel, buttonGroup,     editButton, itemRows,
      moveItemsButton, editNameLine};
  qDebug() << "dumpParents has objects: #" << objects.size();
  for (auto object : objects) {
    if (!object) {
      qDebug() << "An object is null!";
      return;
    }
    qDebug() << "Name:" << object->objectName() << " : Parent:"
             << (object->parent() ? object->parent()->objectName() : "null");
  }
  qDebug() << "\n";
}
