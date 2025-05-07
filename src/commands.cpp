#include "../include/o4_project/container_model.h"

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
