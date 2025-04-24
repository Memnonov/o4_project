#include "../include/o4_project/move_window.h"

MoveWindow::MoveWindow(QWidget *parent)
    : ModeFrame{parent}, leftStack{new QStackedWidget},
      moveSelectedButton{new QPushButton}, rightStack{new QStackedWidget},
      rightContainer{new ContainerWindow}, leftContainer{new ContainerWindow},
      leftItems{new ItemsWindow}, rightItems{new ItemsWindow} {
  leftStack->addWidget(leftContainer);
  leftStack->addWidget(leftItems);
  layout->addWidget(leftStack);

  moveSelectedButton->setIcon(QIcon(":/icons/arrow-separate.svg"));
  moveSelectedButton->setText("Move Selected");
  layout->addWidget(moveSelectedButton);

  rightStack->addWidget(rightContainer);
  rightStack->addWidget(rightItems);
  layout->addWidget(rightStack);

  layout->setStretch(0, 1);
  layout->setStretch(2, 1);
  initConnections();
}

void MoveWindow::initConnections() {
  using Stack = MoveWindow::Stack;
  connect(leftContainer, &ContainerWindow::containerSelected, this,
          [this]() { handleContainerSelected(Stack::left); });
  connect(rightContainer, &ContainerWindow::containerSelected, this,
          [this]() { handleContainerSelected(Stack::right); });
  connect(leftItems, &ItemsWindow::itemsWindowClosed, this,
          [this]() { handleContainerClosed(Stack::left); });
  connect(rightItems, &ItemsWindow::itemsWindowClosed, this,
          [this]() { handleContainerClosed(Stack::right); });
}

void MoveWindow::handleContainerSelected(Stack stack) {
  using Stack = MoveWindow::Stack;
  switch (stack) {
  case Stack::left: {
    leftStack->setCurrentWidget(leftItems);
    break;
  }
  case Stack::right: {
    rightStack->setCurrentWidget(rightItems);
    break;
  }
  }
}

void MoveWindow::handleContainerClosed(Stack stack) {
  using Stack = MoveWindow::Stack;
  switch (stack) {
  case Stack::left: {
    leftStack->setCurrentWidget(leftContainer);
    break;
  }
  case Stack::right: {
    rightStack->setCurrentWidget(rightContainer);
    break;
  }
  }
}
