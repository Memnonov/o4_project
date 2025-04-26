// Copyright [2025] Auli Jussila & Mikko Memonen

#include "../include/o4_project/container_model.h"
#include <QHash>
#include <algorithm>
#include <functional>
#include <memory>
#include <utility>

ContainerModel::ContainerModel(QObject *parent) : QObject{parent} {};


const QVector<std::shared_ptr<Container>>& ContainerModel::getContainers() const {
  return containers;
}

void ContainerModel::addContainer(QString name) {
  containers.push_back(std::move(std::make_shared<Container>(name)));
}

void ContainerModel::removeContainer(unsigned int index) {
  if (index < containers.size()) {
    containers.remove(index);
  }
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
