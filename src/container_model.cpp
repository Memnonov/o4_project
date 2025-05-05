// Copyright [2025] Auli Jussila & Mikko Memonen

#include "../include/o4_project/container_model.h"
#include "../include/o4_project/json_utils.h"
#include <QHash>
#include <algorithm>
#include <functional>
#include <memory>
#include <qlogging.h>
#include <qundostack.h>
#include <utility>

void ContainerModel::initDefaultInventory() {
  containers = JSONUtils::parseInventoryFromFile("./data/data.json");
}

ContainerModel::ContainerModel(QObject *parent) : QObject{parent} {
  connect(&undoStack, &QUndoStack::indexChanged, this, [this] () {
    emit modelChanged(getStatusMessage());
  });
};

bool ContainerModel::contains(Container *container) {
  for (auto const &cont : containers) {
    if (container == cont.get()) {
      return true;
    }
  }
  return false;
}

// TODO: Maybe just return a simple view like QVector<Container*> ?
const QVector<std::shared_ptr<Container>> &
ContainerModel::getContainers() const {
  return containers;
}

void ContainerModel::addContainer(std::shared_ptr<Container> container) {
  containers.push_back(container);
}

void ContainerModel::removeContainer(std::shared_ptr<Container> container) {
  if (containers.contains(container)){
    qDebug() << "Removing container.";
  }
  containers.removeAll(container);
  QMetaObject::invokeMethod(this, [this]() {
    emit this->modelChanged(this->getStatusMessage());
  });
}

QString ContainerModel::getStatusMessage() const {
  if (undoStack.count() == 0 || undoStack.index() == 0) {
    return "Checking your loot.";
  }
  return undoStack.command(undoStack.index() - 1)->text();
}

void ContainerModel::addItem(std::shared_ptr<Item> item,
                             unsigned int contIndex) {
  if (contIndex < containers.size()) {
    containers[contIndex]->addItem(std::move(item));
  }
}

void ContainerModel::removeItem(unsigned int itemIndex,
                                unsigned int contIndex) {
  if (contIndex < containers.size()) {
    containers[contIndex]->removeItem(itemIndex);
  }
}

void ContainerModel::moveItem(unsigned int itemIndex, unsigned int from,
                              unsigned int to) {
  std::shared_ptr<Container> fromCont = getContainer(from);
  std::shared_ptr<Container> toCont = getContainer(to);
  if (fromCont && toCont) {
    fromCont->moveItem(itemIndex, toCont);
  }
}

void ContainerModel::moveItems(unsigned int indexA, unsigned int indexB,
                               QVector<unsigned int> itemsA,
                               QVector<unsigned int> itemsB) {
  std::shared_ptr<Container> contA = getContainer(indexA);
  std::shared_ptr<Container> contB = getContainer(indexB);

  // Checks before committing anything.
  if (!contA || !contB) {
    return;
  }
  for (const auto &index : itemsA) {
    if (index >= contA->size()) {
      return;
    }
  }
  for (const auto &index : itemsB) {
    if (index >= contB->size()) {
      return;
    }
  }

  QHash<std::shared_ptr<Item>, std::shared_ptr<Container>> map;
  std::sort(itemsA.begin(), itemsA.end(), std::greater<unsigned int>());
  std::sort(itemsB.begin(), itemsB.end(), std::greater<unsigned int>());

  // Map items with target containers
  for (const auto &index : itemsA) {
    map.insert(contA->removeItem(index), contB);
  }
  for (const auto &index : itemsB) {
    map.insert(contB->removeItem(index), contA);
  }

  for (const auto &entry : map.asKeyValueRange()) {
    entry.second->addItem(std::move(entry.first));
  }
}

std::shared_ptr<Container>
ContainerModel::getContainer(unsigned int index) const {
  if (index < containers.size()) {
    return containers[index];
  }
  return nullptr;
}

class ContainerModel::NewContainerCmd : public QUndoCommand {
 public:
  NewContainerCmd(ContainerModel *model) : model{model} {
    container = std::make_shared<Container>();
    setText("Created a new command!");
  }
  void undo() override { 
    model->removeContainer(container);
  }
  void redo() override {
    model->addContainer(container);
  }
 private:
  ContainerModel *model;
  std::shared_ptr<Container> container;
};

void ContainerModel::newContainerRequest() {
  undoStack.push(new NewContainerCmd(this));
}
