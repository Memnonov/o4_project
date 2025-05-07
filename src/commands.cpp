#include "../include/o4_project/container_model.h"
#include "../include/o4_project/item.h"
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
    setText(QString{"Created new Container: %1"}.arg(name));
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
    setText(QString{"Removed Container: %1"}.arg(removed->name));
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
  qDebug() << "Requested removal of: " << container->name;
  undoStack.push(new RemoveContainerCmd(this, container));
}

class ContainerModel::ToggleFavouriteCmd : public QUndoCommand {
public:
  ToggleFavouriteCmd(ContainerModel *model, Item *toFavourite,
                     Container *container)
      : model{model}, item{model->getItem(toFavourite, container)} {}
  void redo() override {
    item->favourite = !item->favourite;
    setText(QString{"Marked Item %1 %2."}
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
    setText(QString{"Created Item: %1"}.arg(item->name));
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
  undoStack.push(new NewItemCmd{this, container, name});
}

class ContainerModel::RemoveItemCmd : public QUndoCommand {
public:
  RemoveItemCmd(ContainerModel *model, Item *toRemove, Container *container)
      : model{model}, container{container} {
    if (!toRemove || !container) {
      return;
    }
    item = container->getItem(toRemove);
    setText(QString{"Removed Item: %1"}.arg(item->name));
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
    setText(QString{"Set Item %1 quantity to × %2"}.arg(item->name).arg(newQuantity));
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

// // A lil template, if you will
// class ContainerModel::CMD : public QUndoCommand {
//  public:
//   CMD(ContainerModel *model) : model{model} {
//     // ctor
//   }
//   void redo() override {
//     // redo
//   };
//   void undo() override {
//     // undo
//   };
//  private:
//   ContainerModel *model;
// };
