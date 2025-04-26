#include "../include/o4_project/move_window.h"
#include <qlabel.h>
#include <qnamespace.h>
#include <qsizepolicy.h>
#include <qwidget.h>

MoveWindow::MoveWindow(ContainerModel *model, QWidget *parent)
    : ModeFrame{parent}, model{model}, leftStack{new QStackedWidget},
      middlePanel{new QWidget}, moveSelectedButton{new QPushButton},
      rightStack{new QStackedWidget}, rightContainer{new ContainerWindow{model}},
      leftContainer{new ContainerWindow{model}}, leftItems{new ItemsWindow},
      rightItems{new ItemsWindow} {
  leftStack->addWidget(leftContainer);
  leftStack->addWidget(leftItems);
  leftItems->setMovingItems(true);
  layout->addWidget(leftStack);

  layout->addWidget(getMiddlePanel());

  rightStack->addWidget(rightContainer);
  rightStack->addWidget(rightItems);
  rightItems->setMovingItems(true);
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

QWidget *MoveWindow::getMiddlePanel() {
  auto middlePanel = new QWidget;
  auto panelLayout = new QVBoxLayout{middlePanel};
  // moveSelectedButton->setIcon(QIcon(":/icons/arrow-separate.svg"));
  moveSelectedButton->setContentsMargins(0, 0, 0, 0);
  moveSelectedButton->setText( "→\n←");
  moveSelectedButton->setSizePolicy(QSizePolicy::Preferred,
                                    QSizePolicy::Preferred);
  auto tip = new QLabel("Move all\nselected.");
  tip->setAlignment(Qt::AlignCenter);
  panelLayout->addStretch();
  panelLayout->addWidget(tip);
  panelLayout->addWidget(moveSelectedButton);
  panelLayout->addStretch();
  return middlePanel;
}
