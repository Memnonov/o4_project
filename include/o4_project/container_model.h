// Copyright [2025] Auli Jussila & Mikko Memonen

#ifndef CONTAINER_MODEL
#define CONTAINER_MODEL

#include "./container.h"
#include <QObject>
#include <memory>
#include <qcontainerfwd.h>
#include <qtmetamacros.h>

class ContainerModel;

class ContainerModel : public QObject {
  friend class ContainerModelTests;

  Q_OBJECT;  // semicolon not needed, but makes syntax highlighting behave.

 public:
  ContainerModel() = default;
  ContainerModel(const ContainerModel &) = delete;
  ContainerModel &operator=(const ContainerModel &) = delete;
  ContainerModel(ContainerModel &&) = delete;
  ContainerModel &operator=(ContainerModel &&) = delete;

  void addContainer(QString name = "Unnamed container");
  void removeContainer(unsigned int index);
  void addItem(std::shared_ptr<Item> item, unsigned int contIndex);
  void removeItem(unsigned int itemIndex, unsigned int container);
  void moveItem(unsigned int itemIndex, unsigned int from, unsigned int to);
  void moveItems(unsigned int contA, unsigned int contB,
                 QVector<unsigned int> itemsA, QVector<unsigned int> itemsB);

 private:
  // QVector insists on copyable elements, hence shared.
  QVector<std::shared_ptr<Container>> containers;

  std::shared_ptr<Container> getContainer(unsigned int index) const;
};

#endif  // !CONTAINER_MODEL
