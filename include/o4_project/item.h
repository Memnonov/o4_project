// Copyright [2025] Auli Jussila & Mikko Memonen

#ifndef ITEM_H
#define ITEM_H

#include <QString>
#include <QStringList>

class Item {
 public:
  QString name{"No name"};
  unsigned int quantity{1};
  QString description{"No description"};
  QStringList tags{};

  Item(const QString &name, unsigned int quantity, const QString &description,
       const QStringList &tags)
      : name{name}, quantity{quantity}, description{description}, tags{tags} {}

  Item() = default;
};

#endif  // !ITEM_H
