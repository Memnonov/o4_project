// Copyright [2025] Auli Jussila & Mikko Memonen

#ifndef ITEM_H
#define ITEM_H

#include <QString>
#include <QStringList>
#include <utility>

class Item {
  friend class ContainerModelTests;

 public:
  QString name{"No name"};
  unsigned int quantity{1};
  QString description{"No description"};
  QStringList tags{};
  bool favourite;

  Item(const QString name, unsigned int quantity, const QString description,
       const QStringList tags)
      : name{std::move(name)}, quantity{quantity},
        description{std::move(description)}, tags{std::move(tags)} {}

  explicit Item(const QString name) : Item(name, 1, "", {}) {}

  Item() = default;
};

#endif  // !ITEM_H
