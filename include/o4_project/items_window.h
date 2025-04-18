// Copyright [2025] Auli Jussila & Mikko Memonen

#ifndef ITEMS_WINDOW_H
#define ITEMS_WINDOW_H

#include <QFrame>
#include <QObject>
#include <qboxlayout.h>
#include <QScrollArea>
#include <qpushbutton.h>
#include <qscrollarea.h>
#include <qtoolbar.h>

class ItemsWindow : public QFrame {
  Q_OBJECT;

 public:
  explicit ItemsWindow(QWidget *parent = nullptr);
  ~ItemsWindow() = default;

 private:
  QVBoxLayout* layout;
  QToolBar* filterSortPanel;
  QScrollArea* scrollArea;
  QPushButton* closeButton;
  QPushButton* selectedItemButton;
  QPushButton* bottomDeleteButton;
  
  void createDummyRows(QVBoxLayout *rows);

  signals:
    void itemSelected();
    void closeButtonPushed();
};

#endif // !ITEMS_WINDOW_H
