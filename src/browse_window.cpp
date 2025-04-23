#include "../include/o4_project/browse_window.h"

BrowseWindow::BrowseWindow(QWidget *parent)
    : ModeFrame{parent}, containerWindow{new ContainerWindow},
      itemsWindow{new ItemsWindow}, infoWindow{new ItemInfoWindow},
      leftStack{new QStackedWidget}, rightStack{new QStackedWidget} {
  leftStack->addWidget(containerWindow);
  leftStack->addWidget(itemsWindow);
  rightStack->addWidget(infoWindow);
  layout->addWidget(leftStack);
  layout->addWidget(rightStack);
  layout->setStretch(0, 1);
  layout->setStretch(1, 1);
  initConnections();
}

void BrowseWindow::initConnections() {
  connect(containerWindow, &ContainerWindow::containerSelected, this,
          &BrowseWindow::handleContainerSelected);
  connect(itemsWindow, &ItemsWindow::itemsWindowClosed, this,
          &BrowseWindow::handleItemsWindowClosed);
  connect(itemsWindow, &ItemsWindow::itemSelected, infoWindow,
          &ItemInfoWindow::updateItem);
}

void BrowseWindow::handleContainerSelected() {
  // Actually implement this.
  leftStack->setCurrentWidget(itemsWindow);
}

void BrowseWindow::handleItemsWindowClosed() {
  // Actually implement this.
  leftStack->setCurrentWidget(containerWindow);
  infoWindow->updateItem();
}
