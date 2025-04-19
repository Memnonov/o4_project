// Copyright [2025] Auli Jussila & Mikko Memonen

#ifndef CONTAINERS_WINDOW_H
#define CONTAINERS_WINDOW_H

#include <QFrame>
#include <QObject>
#include <qboxlayout.h>
#include <QScrollArea>
#include <qpushbutton.h>
#include <qscrollarea.h>

class ContainerWindow : public QFrame {
  Q_OBJECT;

 public:
  explicit ContainerWindow(QWidget *parent = nullptr);
  ~ContainerWindow() = default;

 private:
  QVBoxLayout* layout;
  QScrollArea* scrollArea;
  QPushButton* newContainerButton;
  
  void initLabel();
  void initNewContainerButton(QVBoxLayout *rows);
  void createDummyRows(QVBoxLayout *rows);

  signals:
    void containerSelected();
};

#endif // !CONTAINERS_WINDOW_H
