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

class ContainerModel;

class ContainerModel : public QObject {
  friend class ContainerModelTests;
  friend class NewContainerCmd;

  Q_OBJECT;  // semicolon not needed, but makes syntax highlighting behave.

 public:
  ContainerModel(QObject *parent = nullptr);
  void initDefaultInventory();
  void newContainerRequest(const QString &name = "New Container");
  bool contains(Container *container);
  QString getStatusMessage() const;
  QStringList getContainerNames() const;

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
  // QVector insists on copyable elements, hence shared.
  QVector<std::shared_ptr<Container>> containers;
  QUndoStack undoStack;
  void addContainer(std::shared_ptr<Container>);
  void removeContainer(std::shared_ptr<Container>);

  // ----------UndoCommands----------------------
  class NewContainerCmd;
  
  std::shared_ptr<Container> getContainer(unsigned int index) const;
};

#endif  // !CONTAINER_MODEL
