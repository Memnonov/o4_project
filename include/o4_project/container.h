// Copyright [2025] Auli Jussila & Mikko Memonen

#ifndef CONTAINER_H
#define CONTAINER_H

#include <QVector>
#include <item.h>
#include <memory>
#include <utility>

class Container {
 public:
  QString name{"Unnamed Container"};

  explicit Container(const QString& name) : name{name} {}

  Container(const QString& name, const QVector<std::unique_ptr<Item>> items)
      : name{name}, items{std::move(items)} {}

  Container() = default;
  Container(const Container& other) = delete;
  Container& operator=(const Container& other) = delete;

  void addItem(std::unique_ptr<Item> item);
  void removeItem(unsigned int index);
  void moveItem(unsigned int index, Container& other);

 private:
  QVector<std::unique_ptr<Item>> items{};
};

#endif  // !CONTAINER_H
