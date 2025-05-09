#include "../include/o4_project/move_window.h"
#include "container_model.h"
#include "container_window.h"
#include "items_window.h"
#include <qlabel.h>
#include <qlogging.h>
#include <qnamespace.h>
#include <qsizepolicy.h>
#include <qwidget.h>

MoveWindow::MoveWindow(ContainerModel *model, QWidget *parent)
    : ModeFrame{parent}, model{model}, leftStack{new QStackedWidget{this}},
      middlePanel{new QWidget{this}}, moveSelectedButton{new QPushButton{this}},
      rightStack{new QStackedWidget{this}},
      rightItems{new ItemsWindow{rightStack}},
      rightContainer{new ContainerWindow{model, rightStack}},
      leftContainer{new ContainerWindow{model, leftStack}},
      leftItems{new ItemsWindow{leftStack}} {
  setObjectName("MoveWindow");
  leftStack->addWidget(leftContainer);
  leftStack->addWidget(leftItems);
  leftItems->setMovingItems(true);
  layout->addWidget(leftStack);

  layout->addWidget(getMiddlePanel());

  rightStack->addWidget(rightContainer);
  rightStack->addWidget(rightItems);
  rightItems->setMovingItems(true);
  rightItems->setRightWindow(true);
  layout->addWidget(rightStack);

  layout->setStretch(0, 1);
  layout->setStretch(2, 1);
  initConnections();
}

void MoveWindow::refresh() {
  leftContainer->updateRows();
  rightContainer->updateRows();
  leftItems->refresh();
  rightItems->refresh();
}

void MoveWindow::initConnections() {
  using Stack = MoveWindow::Stack;
  connect(leftContainer, &ContainerWindow::containerSelected, this,
          [this]() { handleContainerSelected(Stack::left); });
  connect(leftContainer, &ContainerWindow::containerSelected, leftItems,
          &ItemsWindow::handleContainerSelected);
  connect(rightContainer, &ContainerWindow::containerSelected, this,
          [this]() { handleContainerSelected(Stack::right); });
  connect(rightContainer, &ContainerWindow::containerSelected, rightItems,
          &ItemsWindow::handleContainerSelected);
  for (const auto items : {leftItems, rightItems}) {
    connect(items, &ItemsWindow::containerRenamed, model,
            &ContainerModel::renameContainerRequest);
  }

  // Single item move
  connect(leftItems, &ItemsWindow::moveItemClicked, this,
          [this](const auto &item) {
            moveItem(item, leftItems->getCurrentContainer(),
                     rightItems->getCurrentContainer());
          });
  connect(rightItems, &ItemsWindow::moveItemClicked, this,
          [this](const auto &item) {
            moveItem(item, rightItems->getCurrentContainer(),
                     leftItems->getCurrentContainer());
          });
  // Batch moving
  connect(leftItems, &ItemsWindow::moveAllClicked, this,
          [this](const auto &items) {
            model->batchMoveRequest(items, leftItems->getCurrentContainer(),
                                    rightItems->getCurrentContainer());
            moveSelectedButton->setEnabled(false);
          });
  connect(rightItems, &ItemsWindow::moveAllClicked, this,
          [this](const auto &items) {
            model->batchMoveRequest(items, rightItems->getCurrentContainer(),
                                    leftItems->getCurrentContainer());
            moveSelectedButton->setEnabled(false);
          });
  connect(moveSelectedButton, &QPushButton::clicked, this, [this] {
    auto itemsLeft = leftItems->getSelectedItems();
    auto itemsRight = rightItems->getSelectedItems();
    auto contLeft = leftItems->getCurrentContainer();
    auto contRight = rightItems->getCurrentContainer();
    model->moveAllRequest(itemsLeft, contLeft, itemsRight, contRight);
    moveSelectedButton->setEnabled(false);
  });

  // Toggling the batch move buttons
  connect(leftContainer, &ContainerWindow::containerSelected, this,
          &MoveWindow::updateMoveButtons);
  connect(leftItems, &ItemsWindow::itemSelected, this,
          &MoveWindow::updateMoveButtons);
  connect(leftItems, &ItemsWindow::itemsWindowClosed, this,
          &MoveWindow::updateMoveButtons);

  connect(rightContainer, &ContainerWindow::containerSelected, this,
          &MoveWindow::updateMoveButtons);
  connect(rightItems, &ItemsWindow::itemSelected, this,
          &MoveWindow::updateMoveButtons);
  connect(rightItems, &ItemsWindow::itemsWindowClosed, this,
          &MoveWindow::updateMoveButtons);

  connect(leftItems, &ItemsWindow::itemsWindowClosed, this,
          [this]() { handleContainerClosed(Stack::left); });
  connect(rightItems, &ItemsWindow::itemsWindowClosed, this,
          [this]() { handleContainerClosed(Stack::right); });
  for (const auto &items : {leftItems, rightItems}) {
    connect(items, &ItemsWindow::addNewClicked, model,
            &ContainerModel::newItemRequest);
  }
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
  // auto middlePanel = new QWidget;
  auto panelLayout = new QVBoxLayout{middlePanel};
  // moveSelectedButton->setIcon(QIcon(":/icons/arrow-separate.svg"));
  moveSelectedButton->setContentsMargins(0, 0, 0, 0);
  moveSelectedButton->setText("→\n←");
  moveSelectedButton->setSizePolicy(QSizePolicy::Preferred,
                                    QSizePolicy::Preferred);
  moveSelectedButton->setEnabled(false);
  auto tip = new QLabel("Move all\nselected.");
  tip->setAlignment(Qt::AlignCenter);
  panelLayout->addStretch();
  panelLayout->addWidget(tip);
  panelLayout->addWidget(moveSelectedButton);
  panelLayout->addStretch();
  return middlePanel;
}

void MoveWindow::updateMoveButtons() {
  qDebug() << "@updateMoveButtons()";
  if (!leftItems->hasContainerSelected() ||
      !rightItems->hasContainerSelected()) {
    moveSelectedButton->setEnabled(false);
    leftItems->setCanMoveItems(false);
    rightItems->setCanMoveItems(false);
    qDebug() << "No 2 containers open";
    return;
  }
  leftItems->setCanMoveItems(true);
  rightItems->setCanMoveItems(true);

  bool leftCanMove = leftItems->hasItemSelected();
  bool rightCanMove = rightItems->hasItemSelected();
  qDebug() << "rightCanMove: " << rightCanMove << " | "
           << "leftCanMove: " << leftCanMove;
  moveSelectedButton->setEnabled(leftCanMove | rightCanMove);
}

void MoveWindow::moveItem(Item *item, Container *from, Container *to) {
  model->moveItemRequest(item, from, to);
  moveSelectedButton->setEnabled(false);
}
