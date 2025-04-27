// Copyright [2025] Auli Jussila & Mikko Memonen

#ifndef ITEMS_WINDOW_H
#define ITEMS_WINDOW_H

#include "item.h"
#include "container.h"
#include <QLabel>
#include <QFrame>
#include <QObject>
#include <QScrollArea>
#include <qboxlayout.h>
#include <qbuttongroup.h>
#include <qhash.h>
#include <qlogging.h>
#include <qpushbutton.h>
#include <qscrollarea.h>
#include <qtoolbar.h>

class ItemsWindow : public QFrame {
  Q_OBJECT;

public:
  explicit ItemsWindow(QWidget *parent = nullptr);
  ~ItemsWindow() = default;
  void setMovingItems(bool moving) {
    this->movingItems = moving;
    updateRows();
    moveItemsButton->setVisible(moving);
  }

private:
  Container* currentContainer = nullptr;
  // TODO: Get rid of dummy.
  Item dummyItem{
      "Dummy item",
      666,
      "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod "
      "tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim "
      "veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea "
      "commodo consequat. Duis aute irure dolor in reprehenderit in voluptate "
      "velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint "
      "occaecat cupidatat non proident, sunt in culpa qui officia deserunt "
      "mollit anim id est laborum.",
      {"tag", "tag", "tag"}};

  QVBoxLayout *layout;
  QLabel *title;
  QToolBar *filterSortPanel;
  enum class SortMode { AtoZ, ZtoA, Quantity };
  QHash<SortMode, QString> sortModeToString{
      {ItemsWindow::SortMode::AtoZ, "A-Z"},
      {ItemsWindow::SortMode::ZtoA, "Z-A"},
      {ItemsWindow::SortMode::Quantity, "#"},
  };
  QVBoxLayout *itemRows;
  bool movingItems = false;
  QButtonGroup *buttonGroup;
  SortMode sortMode;
  QScrollArea *scrollArea;
  QPushButton *closeButton;
  QPushButton *selectedItemButton;
  QPushButton *bottomDeleteButton;
  QPushButton *moveItemsButton;

  void createDummyRows(QVBoxLayout *rows);
  void updateRows();
  QString cycleSortMode();
  void closeButtonPushed();

signals:
  void itemSelected(Item *item);
  void itemsWindowClosed();

 public slots:
  void handleContainerSelected(Container *container);
};

#endif // !ITEMS_WINDOW_H
