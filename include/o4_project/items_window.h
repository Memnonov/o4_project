// Copyright [2025] Auli Jussila & Mikko Memonen

#ifndef ITEMS_WINDOW_H
#define ITEMS_WINDOW_H

#include "container.h"
#include "item.h"
#include <QButtonGroup>
#include <QFrame>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QObject>
#include <QPushButton>
#include <QScrollArea>
#include <QStringList>
#include <QVBoxLayout>
#include <QVector>
#include <functional>
#include <qcontainerfwd.h>
#include <qscrollarea.h>
#include <qtoolbar.h>
#include <unordered_map>

class ItemsWindow : public QFrame {
  Q_OBJECT;

public:
  explicit ItemsWindow(QWidget *parent = nullptr);
  ~ItemsWindow() = default;
  void refresh();
  Container *getCurrentContainer();
  void selectItem(Item *item);
  void dumpParents();
  Item *currentItem = nullptr;
  void setDeleteEnabled(bool canDelete) {
    bottomDeleteButton->setEnabled(true);
  }

  void setMovingItems(bool moving) {
    this->movingItems = moving;
    moveItemsButton->setVisible(moving);
    addDeleteWidget->setVisible(!moving);
    buttonGroup->setExclusive(!moving);
  }

  void setRightWindow(bool isRightWindow) {
    this->isRightWindow = isRightWindow;
  }

  bool hasContainerSelected() const { return currentContainer != nullptr; }

  bool hasItemSelected() const;

  QVector<Item *> getSelectedItems() const;

signals:
  void addNewClicked(Container *container, const QString &name);
  void itemSelected(Item *item, Container *container);
  void itemsWindowClosed();
  void deleteItemClicked(Item *item, Container *container);
  void setQuantityClicked(Item *item, unsigned int quantity);
  void moveItemClicked(Item *item);
  void moveItemsClicked(QVector<Item *>);

private:
  enum class SortMode { AtoZ, ZtoA, Quantity };
  QHash<SortMode, QString> sortModeToString{
      {ItemsWindow::SortMode::AtoZ, "A-Z"},
      {ItemsWindow::SortMode::ZtoA, "Z-A"},
      {ItemsWindow::SortMode::Quantity, "#"},
  };

  static const std::unordered_map<
      SortMode, std::function<bool(const Item *, const Item *)>>
      comparators;

  bool movingItems = false;
  bool isRightWindow = false;
  bool editing = false;
  SortMode sortMode = SortMode::AtoZ;

  Container *currentContainer = nullptr;
  QVBoxLayout *layout;
  QLabel *title;
  QToolBar *filterSortPanel;
  QLineEdit *filterInput;
  QVBoxLayout *itemRows;
  QButtonGroup *buttonGroup;
  QPushButton *newButton = nullptr;
  QScrollArea *scrollArea;
  QPushButton *closeButton;
  QPushButton *editButton;
  QPushButton *selectedItemButton;
  QPushButton *bottomDeleteButton;
  QPushButton *moveItemsButton;
  QWidget *addDeleteWidget;
  QLineEdit *editNameLine;

  void updateRows();
  void createRows(QVBoxLayout *rows);
  void initTopRow();
  void initEditButton();
  void initFilterSortPanel();
  QString cycleSortMode();
  void closeButtonPushed();
  void toggleEditing();
  void sortItems(QVector<Item *> &items);
  bool filterItem(Item *item);
  void handleAddNewClicked();

public slots:
  void handleContainerSelected(Container *container);
  void setCanMoveItems(bool canMove);
  void confirmDeleteItem();
};

#endif // !ITEMS_WINDOW_H
