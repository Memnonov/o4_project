// Copyright [2025] Auli Jussila & Mikko Memonen

#include "../include/o4_project/container.h"
#include "../include/o4_project/item.h"
#include <QtLogging>
#include <qdebug.h>
#include <utility>

void Container::addItem(Item item) {
  items.push_back(std::move(item));
}

void Container::removeItem(unsigned int index) {
  if (index < items.size()) {
    items.removeAt(index);
  }
}

void Container::moveItem(unsigned int index, Container& other) {
  if (index < items.size()) {
    other.addItem(std::move(items.takeAt(index)));
  }
}
