#include "../include/o4_project/container_model.h"
#include "../include/o4_project/item.h"
#include "container.h"
#include <memory>
#include <qcontainerfwd.h>
#include <qlogging.h>

class ContainerModel::NewContainerCmd : public QUndoCommand {
public:
  NewContainerCmd(ContainerModel *model, const QString &name = "New Container")
      : model{model} {
    if (name.length() < 1) {
      container = std::make_shared<Container>();
    } else {
      container = std::make_shared<Container>(name);
    }
    setText(QString{"Created new Container: <b>%1</b>"}.arg(name));
  }
  void undo() override { model->removeContainer(container); }
  void redo() override { model->addContainer(container); }

private:
  ContainerModel *model;
  std::shared_ptr<Container> container;
};

void ContainerModel::newContainerRequest(const QString &name) {
  undoStack.push(new NewContainerCmd(this, name));
}

class ContainerModel::RemoveContainerCmd : public QUndoCommand {
public:
  RemoveContainerCmd(ContainerModel *model, Container *toRemove)
      : model{model}, removed{nullptr} {
    this->removed = model->removeContainer(toRemove);
    setText(QString{"Removed Container: <b>%1</b>"}.arg(removed->name));
  }
  void redo() override { model->removeContainer(removed); }
  void undo() override { model->addContainer(removed); }

private:
  ContainerModel *model;
  std::shared_ptr<Container> removed;
};

void ContainerModel::removeContainerRequest(Container *container) {
  if (!container) {
    return;
  }
  undoStack.push(new RemoveContainerCmd(this, container));
}

class ContainerModel::ToggleFavouriteCmd : public QUndoCommand {
public:
  ToggleFavouriteCmd(ContainerModel *model, Item *toFavourite,
                     Container *container)
      : model{model}, item{model->getItem(toFavourite, container)} {}
  void redo() override {
    item->favourite = !item->favourite;
    setText(QString{"Marked Item <b>%1</b> %2."}
                .arg(item->name)
                .arg(item->favourite ? "favourite" : "not favourite"));
  };
  void undo() override { redo(); } // : D

private:
  ContainerModel *model;
  std::shared_ptr<Item> item;
};

void ContainerModel::toggleFavouriteRequest(Item *item, Container *container) {
  if (item && container) {
    undoStack.push(new ToggleFavouriteCmd(this, item, container));
  }
}

class ContainerModel::NewItemCmd : public QUndoCommand {
public:
  NewItemCmd(ContainerModel *model, Container *toContainer, const QString &name)
      : model{model} {
    // Now this is kinda hacky. No regrets. (Actually yes regrets)
    container = model->getContainer(toContainer);
    item = std::make_shared<Item>(name);
    setText(QString{"Created Item: <b>%1</b>"}.arg(item->name));
  }
  void redo() override { container->addItem(item); }
  void undo() override { container->removeItem(item); }

private:
  ContainerModel *model;
  std::shared_ptr<Container> container;
  std::shared_ptr<Item> item;
};

void ContainerModel::newItemRequest(Container *container, const QString &name) {
  if (!container) {
    return;
  }
  undoStack.push(
      new NewItemCmd{this, container, name.length() == 0 ? "New Item" : name});
}

class ContainerModel::RemoveItemCmd : public QUndoCommand {
public:
  RemoveItemCmd(ContainerModel *model, Item *toRemove, Container *container)
      : model{model}, container{container} {
    if (!toRemove || !container) {
      return;
    }
    item = container->getItem(toRemove);
    setText(QString{"Removed Item: <b>%1</b>"}.arg(item->name));
  }
  void redo() override { container->removeItem(item); };
  void undo() override { container->addItem(item); };

private:
  ContainerModel *model;
  Container *container;
  Item *toRemove;
  std::shared_ptr<Item> item = nullptr;
};

void ContainerModel::removeItemRequest(Item *item, Container *container) {
  undoStack.push(new RemoveItemCmd{this, item, container});
}

class ContainerModel::SetItemQuantityCmd : public QUndoCommand {
public:
  SetItemQuantityCmd(ContainerModel *model, Item *item, unsigned int quantity)
      : model{model}, item{item} {
    newQuantity = quantity;
    oldQuantity = item->quantity;
    setText(QString{"Set Item <b>%1</b> quantity to × %2"}
                .arg(item->name)
                .arg(newQuantity));
  }
  void redo() override { item->quantity = newQuantity; };
  void undo() override { item->quantity = oldQuantity; };

private:
  ContainerModel *model;
  Item *item;
  unsigned int newQuantity;
  unsigned int oldQuantity;
};

void ContainerModel::setItemQuantityRequest(Item *item, unsigned int quantity) {
  if (!item) {
    return;
  }
  undoStack.push(new SetItemQuantityCmd{this, item, quantity});
}

class ContainerModel::UpdateItemCmd : public QUndoCommand {
public:
  UpdateItemCmd(ContainerModel *model, Item *item, const Item::ItemData data)
      : model{model}, item{item}, newData{data}, oldData{item->getData()} {
    setText(QString{"Modified Item: "}.arg(data.name));
  }
  void redo() override { item->setData(newData); };
  void undo() override { item->setData(oldData); };

private:
  ContainerModel *model;
  Item *item;
  Item::ItemData newData;
  Item::ItemData oldData;
};

void ContainerModel::updateItemRequest(Item *item, Item::ItemData data) {
  undoStack.push(new UpdateItemCmd{this, item, data});
}

class ContainerModel::MoveItemCmd : public QUndoCommand {
public:
  MoveItemCmd(ContainerModel *model, Item *item, Container *from, Container *to)
      : model{model}, item{item}, from{from}, to{to} {
    setText(QString{"Moved <b>%1</b> from <b>%2</b> to <b>%3</b>"}
                .arg(item->name)
                .arg(from->name)
                .arg(to->name));
  }
  void redo() override { model->moveItem(item, from, to); };
  void undo() override { model->moveItem(item, to, from); };

private:
  ContainerModel *model;
  Item *item;
  Container *from;
  Container *to;
};

void ContainerModel::moveItemRequest(Item *item, Container *from,
                                     Container *to) {
  if (!item || !from || !to) {
    return;
  }
  undoStack.push(new MoveItemCmd{this, item, from, to});
}

class ContainerModel::BatchMoveCmd : public QUndoCommand {
public:
  BatchMoveCmd(ContainerModel *model, QVector<Item *> items, Container *from,
               Container *to)
      : model{model}, items{items}, from{from}, to{to} {
    setText(QString{"Moved %1 Item(s) from <b>%2</b> to <b>%3</b>"}
                .arg(items.size())
                .arg(from->name)
                .arg(to->name));
  }
  void redo() override { to->addItems(from->removeItems(items)); };
  void undo() override { from->addItems(to->removeItems(items)); };

private:
  ContainerModel *model;
  QVector<Item *> items;
  Container *from;
  Container *to;
};

void ContainerModel::batchMoveRequest(QVector<Item *> items, Container *from,
                                      Container *to) {
  if (!from || !to) {
    return;
  }
  if (from == to) {
    return;
  }
  undoStack.push(new BatchMoveCmd{this, items, from, to});
}

class ContainerModel::MoveAllCmd : public QUndoCommand {
public:
  MoveAllCmd(ContainerModel *model, QVector<Item *> itemsA, Container *contA,
             QVector<Item *> itemsB, Container *contB)
      : model{model} {
    commands.push_back(
        std::make_shared<BatchMoveCmd>(model, itemsA, contA, contB));
    commands.push_back(
        std::make_shared<BatchMoveCmd>(model, itemsB, contB, contA));
    setText(QString{"Moved %1 Item(s) between <b>%2</b> and <b>%3</b>"}
                .arg(itemsA.size() + itemsB.size())
                .arg(contA->name)
                .arg(contB->name));
  }
  void redo() override {
    for (const auto &command : commands) {
      command->redo();
    }
  };
  void undo() override {
    for (const auto &command : commands) {
      command->undo();
    }
  };

private:
  ContainerModel *model;
  QVector<std::shared_ptr<BatchMoveCmd>> commands;
};

void ContainerModel::moveAllRequest(QVector<Item *> itemsA, Container *contA,
                                    QVector<Item *> itemsB, Container *contB) {
  undoStack.push(new MoveAllCmd{this, itemsA, contA, itemsB, contB});
}

class ContainerModel::RenameContainerCmd : public QUndoCommand {
public:
  RenameContainerCmd(ContainerModel *model, Container *container,
                     const QString &name)
      : model{model}, container{container}, newName{name} {
    oldName = name;
  }
  void redo() override { container->name = newName; };
  void undo() override { container->name = oldName; };

private:
  ContainerModel *model;
  Container *container;
  QString oldName;
  QString newName;
};

void ContainerModel::renameContainerRequest(Container *container, const QString &name) {
  undoStack.push(new RenameContainerCmd{this, container, name});
}
