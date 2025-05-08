// Copyright [2025] Auli Jussila & Mikko Memonen

#include "../include/o4_project/container.h"
#include "../include/o4_project/item.h"
#include <QtLogging>
#include <algorithm>
#include <memory>
#include <qdebug.h>
#include <QtLogging>
#include <qlogging.h>
#include <qvector.h>
#include <utility>

QVector<Item*> Container::getItems() const {
  QVector<Item*> items;
  for (auto const &item : this->items) {
    items.push_back(item.get());
  }
  return items;
}

const QVector<std::shared_ptr<Item>> &Container::getItemRefs() const {
  return items;
}

void Container::addItem(std::shared_ptr<Item> item) {
  if (!item) {
    return;
  }
  qDebug() << "Adding item: " << item->name;
  items.push_back(std::move(item));
}

std::shared_ptr<Item> Container::getItem(Item *item) {
  for (auto const &element : items) {
    if (item == element.get()) {
      return element;
    }
  }
  return nullptr;
}

std::shared_ptr<Item> Container::removeItem(unsigned int index) {
  if (index < items.size()) {
    return items.takeAt(index);
  }
  return nullptr;
}

std::shared_ptr<Item> Container::removeItem(std::shared_ptr<Item> item) {
  auto it = std::find(items.begin(), items.end(), item);
  if (it == items.end()) {
    return nullptr;
  }
  auto temp = *it;
  items.erase(it);
  return temp;
}

std::shared_ptr<Item> Container::removeItem(Item *item) {
  auto it = QMutableVectorIterator<std::shared_ptr<Item>>(items);
  while (it.hasNext()) {
    if (it.next().get() == item) {
      auto temp = it.value();
      it.remove();
      qDebug() << "removeItem (Item *item) found item: " << temp->name;
      return temp;
    }
  }
  return nullptr;
}

void Container::moveItem(unsigned int index, std::shared_ptr<Container> other) {
  if (index < items.size()) {
    other->addItem(std::move(items.takeAt(index)));
  }
}

unsigned int Container::size() const {
  return items.size();
}
