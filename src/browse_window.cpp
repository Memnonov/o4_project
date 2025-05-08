#include "../include/o4_project/browse_window.h"
#include "container_model.h"
#include "items_window.h"
#include <qlogging.h>

BrowseWindow::BrowseWindow(ContainerModel *model, QWidget *parent)
    : ModeFrame{parent}, model{model},
      containerWindow{new ContainerWindow{model}}, itemsWindow{new ItemsWindow},
      infoWindow{new ItemInfoWindow}, leftStack{new QStackedWidget},
      rightStack{new QStackedWidget} {
  if (model) {
    qDebug() << "Browse window has a model.";
  }
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
  // Internal connections
  connect(containerWindow, &ContainerWindow::containerSelected, this,
          &BrowseWindow::handleContainerSelected);
  connect(itemsWindow, &ItemsWindow::itemsWindowClosed, this,
          &BrowseWindow::handleItemsWindowClosed);
  connect(itemsWindow, &ItemsWindow::itemSelected, infoWindow,
          &ItemInfoWindow::handleItemSelected);
  connect(containerWindow, &ContainerWindow::containerSelected, itemsWindow,
          &ItemsWindow::handleContainerSelected);
  connect(itemsWindow, &ItemsWindow::itemSelected, infoWindow,
          &ItemInfoWindow::handleItemSelected);
  connect(itemsWindow, &ItemsWindow::deleteItemClicked, infoWindow,
          &ItemInfoWindow::clearSelection);

  // External connections
  connect(infoWindow, &ItemInfoWindow::favouriteButtonClicked, model,
          &ContainerModel::toggleFavouriteRequest);
  connect(itemsWindow, &ItemsWindow::addNewClicked, model,
          &ContainerModel::newItemRequest);
  connect(itemsWindow, &ItemsWindow::deleteItemClicked, model,
          &ContainerModel::removeItemRequest);
  connect(itemsWindow, &ItemsWindow::setQuantityClicked, model,
          &ContainerModel::setItemQuantityRequest);
  connect(infoWindow, &ItemInfoWindow::itemUpdated, model,
          &ContainerModel::updateItemRequest);
}

void BrowseWindow::handleContainerSelected(Container *container) {
  leftStack->setCurrentWidget(itemsWindow);
}

void BrowseWindow::handleItemsWindowClosed() {
  // Actually implement this.
  leftStack->setCurrentWidget(containerWindow);
  infoWindow->handleItemSelected();
}

void BrowseWindow::refresh() {
  containerWindow->updateRows();
  if (!model->contains(itemsWindow->getCurrentContainer())) {
    leftStack->setCurrentWidget(containerWindow);
    infoWindow->handleItemSelected();
    infoWindow->clearSelection();
  }
  itemsWindow->refresh();
  infoWindow->refresh();
}

void BrowseWindow::handleGoToItem(Item *item, Container *container) {
  if (!item || !container) {
    return;
  }
  handleContainerSelected(container);
  containerWindow->containerSelected(container);
  itemsWindow->itemSelected(item, container);
  itemsWindow->selectItem(item);
  itemsWindow->setDeleteEnabled(true);
}
