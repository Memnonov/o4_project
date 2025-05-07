// Copyright [2025] Auli Jussila & Mikko Memonen

#ifndef CONTAINER_MODEL
#define CONTAINER_MODEL

#include "./container.h"
#include <QObject>
#include <memory>
#include <qcontainerfwd.h>
#include <qlogging.h>
#include <qtextdocument.h>
#include <qtmetamacros.h>
#include <QUndoStack>
#include <QUndoCommand>
#include <qundostack.h>
#include "item.h"

class ContainerModel;

class ContainerModel : public QObject {
  // ----------UndoCommands----------------------
  // Implemented in commands.cpp
  class NewContainerCmd;
  class RemoveContainerCmd;
  class ToggleFavouriteCmd;
  class NewItemCmd;
  
  friend class ContainerModelTests;
  friend class NewContainerCmd;
  friend class RemoveContainerCmd;
  friend class SetItemFavouriteCmd;
  friend class NewItemCmd;

  Q_OBJECT;  // semicolon not needed, but makes syntax highlighting behave.

 public:
  ContainerModel(QObject *parent = nullptr);
  void initDefaultInventory();
  bool contains(Container *container);
  QString getStatusMessage() const;
  std::shared_ptr<Container> getContainer(Container *container) const;
  QStringList getContainerNames() const;
  std::shared_ptr<Item> getItem(Item *item, Container *container) const;
  
  void newContainerRequest(const QString &name = "New Container");
  void removeContainerRequest(Container *container);
  void toggleFavouriteRequest(Item *item, Container *container);
  void newItemRequest(Container *container, const QString &name);

  const QVector<std::shared_ptr<Container>>& getContainers() const;
  void addItem(std::shared_ptr<Item> item, unsigned int contIndex);
  void removeItem(unsigned int itemIndex, unsigned int container);
  void moveItem(unsigned int itemIndex, unsigned int from, unsigned int to);
  void moveItems(unsigned int contA, unsigned int contB,
                 QVector<unsigned int> itemsA, QVector<unsigned int> itemsB);

 public slots:
  void handleUndo() { undoStack.undo(); qDebug() << "handling undo"; }
  void handleRedo() { undoStack.redo(); qDebug() << "handling redo"; }

 signals:
  void modelChanged(QString message);

 private:
  QVector<std::shared_ptr<Container>> containers;
  QUndoStack undoStack;
  void addContainer(std::shared_ptr<Container>);
  void removeContainer(std::shared_ptr<Container>);
  std::shared_ptr<Container> removeContainer(Container *container);

  
  std::shared_ptr<Container> getContainer(unsigned int index) const;
};

#endif  // !CONTAINER_MODEL
