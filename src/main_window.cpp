// Copyright [2025] Auli Jussila & Mikko Memonen

#include "../include/o4_project/main_window.h"
#include "../include/o4_project/navigation_window.h"
#include "container_window.h"
#include <QHBoxLayout>
#include <QtLogging>
#include <qboxlayout.h>
#include <qsizepolicy.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), navigationWindow{new NavigationWindow},
      containerWindow{new ContainerWindow} {
  QWidget *central = new QWidget(this);
  QHBoxLayout *layout = new QHBoxLayout(central);
  setCentralWidget(central);

  connect(navigationWindow, &NavigationWindow::buttonPressed, this,
          &MainWindow::handleNavigation);

  ContainerWindow *dummyA = new ContainerWindow;
  ContainerWindow *dummyB = new ContainerWindow;
  ContainerWindow *dummyC = new ContainerWindow;
  layout->addWidget(navigationWindow);
  layout->addWidget(containerWindow);
  layout->addWidget(dummyC);

  layout->setStretch(0, 1);
  layout->setStretch(1, 2);
  layout->setStretch(2, 2);
}

// A placeholder for actual behaviour.
void MainWindow::handleNavigation(NavigationWindow::NavAction action) {
  qDebug() << "Pressed navigation button: "
           << NavigationWindow::navActionToString(action);
}
