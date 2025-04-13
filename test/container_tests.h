// Copyright [2025] Auli Jussila & Mikko Memonen

#include "../include/o4_project/container.h"
#include "../include/o4_project/item.h"
#include <QObject>
#include <QStringList>
#include <QTest>
#include <QtLogging>
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
  container.addItem(
      Item("Testing Item A", 1, "Test description...", QStringList{}));
  container.addItem(
      Item("Testing Item B", 1, "Test description...", QStringList{}));
  QCOMPARE(container.items.size(), 2);
}

inline void ContainerTests::testRemoveItem() {
  Container container;
  container.addItem(
      Item("Testing Item A", 1, "Test description...", QStringList{}));
  container.addItem(
      Item("Testing Item B", 1, "Test description...", QStringList{}));
  container.removeItem(1);
  container.removeItem(0);
  container.addItem(
    Item("Testing Item C", 1, "Test description...", QStringList{}));
  container.removeItem(666);
  QCOMPARE(container.items.size(), 1);
}

inline void ContainerTests::testMoveItem() {
  Container origin;
  Container target;
  origin.addItem(
      Item("Testing Item A", 1, "Test description...", QStringList{}));
  origin.addItem(
      Item("Testing Item B", 1, "Test description...", QStringList{}));
  origin.moveItem(0, target);
  origin.moveItem(0, target);
  QCOMPARE(origin.items.size(), 0);
  QCOMPARE(target.items.size(), 2);
}
