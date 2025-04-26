// Copyright [2025] Auli Jussila & Mikko Memonen

#ifndef ITEM_H
#define ITEM_H

#include <QString>
#include <QStringList>
#include <QStringLiteral>
#include <qstringliteral.h>

class Item {
  friend class ContainerModelTests;

public:
  QString name{QStringLiteral("New Item")};
  unsigned int quantity{1};
  QString description{QStringLiteral("No description.")};
  QStringList tags{};
  bool favourite = false;

  Item(const QString &name, unsigned int quantity, const QString &description,
       const QStringList &tags, const bool favourite = false)
      : name{name}, quantity{quantity}, description{description}, tags{tags},
        favourite{favourite} {}

  explicit Item(const QString name) : Item(name, 1, "", {}) {}
};

#endif // !ITEM_H
