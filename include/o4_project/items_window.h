// Copyright [2025] Auli Jussila & Mikko Memonen

#ifndef ITEMS_WINDOW_H
#define ITEMS_WINDOW_H

#include "item.h"
#include "container.h"
#include <QLineEdit>
#include <QLabel>
#include <QFrame>
#include <QObject>
#include <QScrollArea>
#include <functional>
#include <qboxlayout.h>
#include <qbuttongroup.h>
#include <qcontainerfwd.h>
#include <qhash.h>
#include <qlogging.h>
#include <qpushbutton.h>
#include <qscrollarea.h>
#include <qtoolbar.h>
#include <unordered_map>
#include <QMessageBox>
#include <QVector>
#include <QStringList>

class ItemsWindow : public QFrame {
  Q_OBJECT;

public:
  explicit ItemsWindow(QWidget *parent = nullptr);
  ~ItemsWindow() = default;
  void refresh();
  Container *getCurrentContainer();
  
  void setMovingItems(bool moving) {
    this->movingItems = moving;
    moveItemsButton->setVisible(moving);
    addDeleteWidget->setVisible(!moving);
    buttonGroup->setExclusive(!moving);
  }

  void setRightWindow(bool isRightWindow) {
    this->isRightWindow = isRightWindow;
  }

  bool hasContainerSelected() const {
    return currentContainer != nullptr;
  }
  
  bool hasItemSelected() const;

  QVector<Item*> getSelectedItems() const;

private:
  enum class SortMode { AtoZ, ZtoA, Quantity };
  QHash<SortMode, QString> sortModeToString{
      {ItemsWindow::SortMode::AtoZ, "A-Z"},
      {ItemsWindow::SortMode::ZtoA, "Z-A"},
      {ItemsWindow::SortMode::Quantity, "#"},
  };
  
  static const std::unordered_map<SortMode, std::function<bool(const Item*, const Item*)>> comparators;

  bool movingItems = false;
  bool isRightWindow = false;
  bool editing = false;
  SortMode sortMode = SortMode::AtoZ;
  
  Container* currentContainer = nullptr;
  QVBoxLayout *layout;
  QLabel *title;
  QToolBar *filterSortPanel;
  QVBoxLayout *itemRows;
  QButtonGroup *buttonGroup;
  QScrollArea *scrollArea;
  QPushButton *closeButton;
  QPushButton *editButton;
  QPushButton *selectedItemButton;
  QPushButton *bottomDeleteButton;
  QPushButton *moveItemsButton;
  QWidget *addDeleteWidget;
  QLineEdit *editNameLine;

  void updateRows();
  void createDummyRows(QVBoxLayout *rows);
  void initEditButton();
  QString cycleSortMode();
  void closeButtonPushed();
  void toggleEditing();
  void sortItems(QVector<Item*> &items);

signals:
  void itemSelected(Item *item, Container *container);
  void itemsWindowClosed();

 public slots:
  void handleContainerSelected(Container *container);
  void setCanMoveItems(bool canMove);
  void confirmDeleteItem();
};

#endif // !ITEMS_WINDOW_H
