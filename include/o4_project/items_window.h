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
    addDeleteWidget->setVisible(!moving);
  }

private:
  Container* currentContainer = nullptr;

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
  QWidget *addDeleteWidget;
  // QHBoxLayout

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
