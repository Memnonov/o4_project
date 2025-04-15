// Copyright [2025] Auli Jussila & Mikko Memonen

#ifndef CONTAINERS_WINDOW_H
#define CONTAINERS_WINDOW_H

#include <QFrame>
#include <QObject>
#include <qboxlayout.h>
#include <QScrollArea>
#include <qscrollarea.h>

class ContainerWindow : public QFrame {
  Q_OBJECT;

 public:
  explicit ContainerWindow(QWidget *parent = nullptr);
  ~ContainerWindow() = default;

 private:
  QVBoxLayout* layout;
  QScrollArea* scrollArea;
};

#endif // !CONTAINERS_WINDOW_H
