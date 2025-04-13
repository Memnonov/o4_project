// Copyright [2025] Auli Jussila & Mikko Memonen

#ifndef CONTAINER_H
#define CONTAINER_H

#include <QVector>
#include "./item.h"
#include <utility>

class Container;

class Container {
  friend class ContainerTests;

 public:
  QString name{"Unnamed Container"};

  explicit Container(const QString& name) : name{name} {}

  Container(const QString& name, const QVector<Item> items)
      : name{name}, items{std::move(items)} {}

  Container() = default;
  Container(const Container& other) = delete;
  Container& operator=(const Container& other) = delete;

  void addItem(Item item);
  void removeItem(unsigned int index);
  void moveItem(unsigned int index, Container& other);

 private:
  QVector<Item> items{};
};

#endif  // !CONTAINER_H
