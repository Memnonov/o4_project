// Copyright [2025] Auli Jussila & Mikko Memonen

#include "../include/o4_project/container.h"
#include "../include/o4_project/item.h"
#include <QtLogging>
#include <memory>
#include <qdebug.h>
#include <utility>

void Container::addItem(std::shared_ptr<Item> item) {
  items.push_back(std::move(item));
}

std::shared_ptr<Item> Container::removeItem(unsigned int index) {
  if (index < items.size()) {
    return items.takeAt(index);
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
