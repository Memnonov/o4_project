// Copyright [2025] Auli Jussila & Mikko Memonen

#ifndef CONTAINER_TESTS
#define CONTAINER_TESTS

#include "../include/o4_project/container.h"
#include "../include/o4_project/item.h"
#include <QObject>
#include <QStringList>
#include <QTest>
#include <QtLogging>
#include <memory>
#include <qtestcase.h>

class ContainerTests : public QObject {
  Q_OBJECT;

 private slots:
  void testAddItem();
  void testRemoveItem();
  void testMoveItem();
};

inline void ContainerTests::testAddItem() {
  Container container;
  container.addItem(std::make_shared<Item>(
      Item("Testing Item A", 1, "Test description...", QStringList{})));
  container.addItem(std::make_shared<Item>(
      Item("Testing Item B", 1, "Test description...", QStringList{})));
  QCOMPARE(container.items.size(), 2);
}

inline void ContainerTests::testRemoveItem() {
  Container container;
  container.addItem(std::make_shared<Item>(
      Item("Testing Item A", 1, "Test description...", QStringList{})));
  container.addItem(std::make_shared<Item>(
      Item("Testing Item B", 1, "Test description...", QStringList{})));
  container.removeItem((unsigned int) 1); // meh
  container.removeItem((unsigned int) 0);
  container.addItem(std::make_shared<Item>(
      Item("Testing Item C", 1, "Test description...", QStringList{})));
  container.removeItem(666);
  QCOMPARE(container.items.size(), 1);
}

inline void ContainerTests::testMoveItem() {
  auto from = std::make_shared<Container>();
  auto to = std::make_shared<Container>();
  from->addItem(std::make_shared<Item>(
      Item("Testing Item A", 1, "Test description...", QStringList{})));
  to->addItem(std::make_shared<Item>(
      Item("Testing Item B", 1, "Test description...", QStringList{})));
  from->moveItem(0, to);
  from->moveItem(0, to);
  QCOMPARE(from->items.size(), 0);
  QCOMPARE(to->items.size(), 2);
}

#endif  // !CONTAINER_TESTS
