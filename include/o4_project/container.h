// Copyright [2025] Auli Jussila & Mikko Memonen

#ifndef CONTAINER_H
#define CONTAINER_H

#include <QVector>
#include "./item.h"
#include <memory>
#include <utility>

class Container;

class Container {
  friend class ContainerTests;
  friend class ContainerModelTests;

 public:
  QString name{"Unnamed Container"};
  const QVector<std::shared_ptr<Item>> getItems() const;

  explicit Container(const QString& name) : name{name} {}

  Container(const QString& name, const QVector<std::shared_ptr<Item>> items)
      : name{name}, items{std::move(items)} {}

  Container() = default;
  Container(const Container& other) = delete;
  Container& operator=(const Container& other) = delete;

  void addItem(std::shared_ptr<Item> item);
  std::shared_ptr<Item> removeItem(unsigned int index);
  void moveItem(unsigned int index, std::shared_ptr<Container> other);
  unsigned int size() const;

 private:
  QVector<std::shared_ptr<Item>> items{};
};

#endif  // !CONTAINER_H
