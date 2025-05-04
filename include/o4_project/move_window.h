// Copyright [2025] Auli Jussila & Mikko Memonen

#ifndef MOVE_WINDOW_H
#define MOVE_WINDOW_H

#include "container_window.h"
#include "items_window.h"
#include "mode_frame.h"
#include <QStackedWidget>
#include "container_model.h"

class MoveWindow : public ModeFrame {
public:
  MoveWindow(ContainerModel *model, QWidget *parent = nullptr);
  ~MoveWindow() {}

private:
  enum class Stack { right, left };


  ContainerModel *model;
  QWidget *middlePanel;
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
  QWidget* getMiddlePanel();
  void handleContainerSelected(Stack stack);
  void handleContainerClosed(Stack stack);
  void updateMoveSelectedButton();
};

#endif // !MOVE_WINDOW_H
