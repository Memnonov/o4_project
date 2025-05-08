// Copyright [2025] Auli Jussila & Mikko Memonen

#ifndef CONTAINER_MODEL
#define CONTAINER_MODEL

#include "./container.h"
#include "item.h"
#include <QObject>
#include <QUndoCommand>
#include <QUndoStack>
#include <memory>

class ContainerModel;

class ContainerModel : public QObject {
  Q_OBJECT; // semicolon not needed, but makes syntax highlighting behave.

public:
  ContainerModel(QObject *parent = nullptr);
  void initDefaultInventory();
  bool contains(Container *container);
  QString getStatusMessage() const;
  std::shared_ptr<Container> getContainer(Container *container) const;
  QStringList getContainerNames() const;
  std::shared_ptr<Item> getItem(Item *item, Container *container) const;

  const QVector<std::shared_ptr<Container>> &getContainers() const;
  // These below ended up kinda useless ?
  void addItem(std::shared_ptr<Item> item, unsigned int contIndex);
  void removeItem(unsigned int itemIndex, unsigned int container);
  void moveItem(unsigned int itemIndex, unsigned int from, unsigned int to);
  void moveItem(Item *item, Container *from, Container *to);
  void moveItems(unsigned int contA, unsigned int contB,
                 QVector<unsigned int> itemsA, QVector<unsigned int> itemsB);
  void moveItems(QVector<Item *> items, Container *from, Container *to);

  // Changes to the model are made through these requests
  void newContainerRequest(const QString &name = "New Container");
  void removeContainerRequest(Container *container);
  void toggleFavouriteRequest(Item *item, Container *container);
  void newItemRequest(Container *container, const QString &name);
  void removeItemRequest(Item *item, Container *container);
  void setItemQuantityRequest(Item *item, unsigned int quantity);
  void updateItemRequest(Item *item, Item::ItemData data);
  void moveItemRequest(Item *item, Container *from, Container *to);
  void batchMoveRequest(QVector<Item *> items, Container *from, Container *to);
  void moveAllRequest(QVector<Item *> itemsA, Container *contA,
                      QVector<Item *> itemsB, Container *contB);

public slots:
  void handleUndo() { undoStack.undo(); }
  void handleRedo() { undoStack.redo(); }

signals:
  void modelChanged(QString message);

private:
  // ----------UndoCommands----------------------
  // Implemented in commands.cpp
  class NewContainerCmd;
  class RemoveContainerCmd;
  class ToggleFavouriteCmd;
  class NewItemCmd;
  class RemoveItemCmd;
  class SetItemQuantityCmd;
  class UpdateItemCmd;
  class MoveItemCmd;
  class BatchMoveCmd;
  class MoveAllCmd;

  friend class ContainerModelTests;
  friend class NewContainerCmd;
  friend class RemoveContainerCmd;
  friend class SetItemFavouriteCmd;
  friend class NewItemCmd;
  friend class RemoveItemCmd;
  friend class SetItemQuantityCmd;
  friend class UpdateItemCmd;
  friend class MoveItemCmd;
  friend class BatchMoveCmd;
  friend class MoveAllCmd;

  QVector<std::shared_ptr<Container>> containers;
  QUndoStack undoStack;
  void addContainer(std::shared_ptr<Container>);
  void removeContainer(std::shared_ptr<Container>);
  std::shared_ptr<Container> removeContainer(Container *container);

  std::shared_ptr<Container> getContainer(unsigned int index) const;
};

#endif // !CONTAINER_MODEL
