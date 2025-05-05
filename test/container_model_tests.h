// Copyright [2025] Auli Jussila & Mikko Memonen

#ifndef CONTAINER_MODEL_TESTS
#define CONTAINER_MODEL_TESTS

#include "../include/o4_project/container_model.h"
#include <QObject>
#include <QTest>
#include <QtLogging>
#include <memory>
#include <qtestcase.h>
#include <utility>

class ContainerModelTests : public QObject {
  Q_OBJECT;

 private slots:
  void testAddContainer();
  void testRemoveContainer();
  void testMoveItems();
};

inline void ContainerModelTests::testAddContainer() {
  ContainerModel model;
  auto contA = std::make_shared<Container>();
  auto contB = std::make_shared<Container>();
  model.addContainer(contA);
  model.addContainer(contB);
  QCOMPARE(model.containers.size(), 2);
}

inline void ContainerModelTests::testRemoveContainer() {
  ContainerModel model;
  auto contA = std::make_shared<Container>();
  auto contB = std::make_shared<Container>();
  model.addContainer(contA);
  model.addContainer(contB);
  model.removeContainer(0);
  QCOMPARE(model.containers.size(), 1);
}

inline void ContainerModelTests::testMoveItems() {
  ContainerModel model;

  auto contA = std::make_shared<Container>("Testi A");
  auto contB = std::make_shared<Container>("Testi B");
  
  model.addContainer(contA);
  QVERIFY(model.containers[0]->name == "Testi A");
  model.addItem(std::move(std::make_shared<Item>("Moves to B")), 0);
  QVERIFY(model.containers[0]->items[0]->name == "Moves to B");

  model.addContainer(contB);
  QVERIFY(model.containers[1]->name == "Testi B");
  model.addItem(std::move(std::make_shared<Item>("Moves to A")), 1);
  QVERIFY(model.containers[1]->items[0]->name == "Moves to A");

  model.moveItems(0, 1, {0}, {0});
  QCOMPARE(model.containers[0]->items[0]->name, "Moves to A");
  QCOMPARE(model.containers[1]->items[0]->name, "Moves to B");
}

#endif  // !CONTAINER_MODEL_TESTS
