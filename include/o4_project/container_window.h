// Copyright [2025] Auli Jussila & Mikko Memonen

#ifndef CONTAINERS_WINDOW_H
#define CONTAINERS_WINDOW_H

#include <QFrame>
#include <QObject>
#include <memory>
#include <qboxlayout.h>
#include <QScrollArea>
#include <qcontainerfwd.h>
#include <qpushbutton.h>
#include <qscrollarea.h>
#include "container.h"
#include "container_model.h"

class ContainerWindow : public QFrame {
  Q_OBJECT;

 public:
  explicit ContainerWindow(ContainerModel *model, QWidget *parent = nullptr);
  ~ContainerWindow() = default;

 private:
  ContainerModel *model;
  QVBoxLayout *rows;
  QVBoxLayout* layout;
  QScrollArea* scrollArea;
  QPushButton* newContainerButton;
  
  void initLabel();
  void initNewContainerButton(QVBoxLayout *rows);
  void updateRows();
  void clearRows();
  const QVector<std::shared_ptr<Container>> getContainers() const;

  signals:
    void containerSelected(Container *container);
};

#endif // !CONTAINERS_WINDOW_H
