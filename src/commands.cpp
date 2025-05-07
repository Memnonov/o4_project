#include "../include/o4_project/container_model.h"
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
