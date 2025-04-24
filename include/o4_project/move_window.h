// Copyright [2025] Auli Jussila & Mikko Memonen

#ifndef MOVE_WINDOW_H
#define MOVE_WINDOW_H

#include "container_window.h"
#include "items_window.h"
#include "mode_frame.h"
#include <QStackedWidget>

class MoveWindow : public ModeFrame {
public:
  MoveWindow(QWidget *parent = nullptr);
  ~MoveWindow() {}

private:
  enum class Stack { right, left };

  QPushButton *moveSelectedButton;
  QStackedWidget *leftStack;
  QStackedWidget *rightStack;
  ContainerWindow *leftContainer;
  ContainerWindow *rightContainer;
  ItemsWindow *leftItems;
  ItemsWindow *rightItems;

  // Makes this concrete.
  virtual void dummyFunction() {}
  void initConnections();

private slots:
  void handleContainerSelected(Stack stack);
  void handleContainerClosed(Stack stack);
};

#endif // !MOVE_WINDOW_H
