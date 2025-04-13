// Copyright [2025] Auli Jussila & Mikko Memonen

#ifndef CONTAINER_MODEL
#define CONTAINER_MODEL

#include "./container.h"
#include <QObject>
#include <memory>
#include <qcontainerfwd.h>
#include <qtmetamacros.h>

class ContainerModel : public QObject {
  Q_OBJECT

 public:
  void addItem(unsigned int itemIndex, unsigned int container);
  void removeItem(unsigned int itemIndex, unsigned int container);
  void moveItem(unsigned int itemIndex, unsigned int fromContainer,
                unsigned int toContainer);
  void batchMoveItems(unsigned int containerA, unsigned int containerB,
                      QVector<unsigned int> itemsA,
                      QVector<unsigned int> itemsB);

 private:
  // QVector insists on copyable elements, hence shared...
  QVector<std::shared_ptr<Container>> containers;

  std::shared_ptr<Container> getContainer(unsigned int index) {
    if (index < containers.size()) {
      return containers[index];
    }
    return nullptr;
  }
};

#endif  // !CONTAINER_MODEL
