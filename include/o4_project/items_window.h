// Copyright [2025] Auli Jussila & Mikko Memonen

#ifndef ITEMS_WINDOW_H
#define ITEMS_WINDOW_H

#include <QFrame>
#include <QObject>
#include <QScrollArea>
#include <qboxlayout.h>
#include <qhash.h>
#include <qpushbutton.h>
#include <qscrollarea.h>
#include <qtoolbar.h>

class ItemsWindow : public QFrame {
  Q_OBJECT;

 public:
  explicit ItemsWindow(QWidget *parent = nullptr);
  ~ItemsWindow() = default;

 private:
  QVBoxLayout *layout;
  QToolBar *filterSortPanel;
  enum class SortMode { AtoZ, ZtoA, Quantity };
  QHash<SortMode, QString> sortModeToString{
      {ItemsWindow::SortMode::AtoZ, "A-Z"},
      {ItemsWindow::SortMode::ZtoA, "Z-A"},
      {ItemsWindow::SortMode::Quantity, "#"},
  };
  SortMode sortMode;
  QScrollArea *scrollArea;
  QPushButton *closeButton;
  QPushButton *selectedItemButton;
  QPushButton *bottomDeleteButton;

  void createDummyRows(QVBoxLayout *rows);
  QString cycleSortMode();

signals:
  void itemSelected();
  void closeButtonPushed();
};

#endif // !ITEMS_WINDOW_H
