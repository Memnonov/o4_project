// Copyright [2025] Auli Jussila & Mikko Memonen

#include "../include/o4_project/main_window.h"
#include "../include/o4_project/navigation_window.h"
#include "container_window.h"
#include <QHBoxLayout>
#include <QStackedWidget>
#include <QtLogging>
#include <qboxlayout.h>
#include <qlabel.h>
#include <qlogging.h>
#include <qpushbutton.h>
#include <qsizepolicy.h>
#include <qstackedwidget.h>
#include <qwidget.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), navigationWindow{new NavigationWindow},
      containerWindow{new ContainerWindow}, stack{new QStackedWidget} {
  QWidget *central = new QWidget(this);
  QHBoxLayout *layout = new QHBoxLayout(central);
  setCentralWidget(central);

  connect(navigationWindow, &NavigationWindow::buttonPressed, this,
          &MainWindow::handleNavigation);
  connect(containerWindow, &ContainerWindow::containerSelected, this,
          &MainWindow::handleContainerClicked);

  auto dummyA = new ContainerWindow;
  auto dummyB = new ContainerWindow;
  auto dummyC = new ContainerWindow;
  auto dummyWidget = new QWidget;
  auto dummyLayout = new QVBoxLayout;
  dummyLayout->addWidget(new QLabel{"Dummy!"});
  auto backButton = new QPushButton{"Back"};
  connect(backButton, &QPushButton::clicked, this, &MainWindow::handleBackButton);
  dummyLayout->addWidget(backButton);
  dummyWidget->setLayout(dummyLayout);
  openContainerWindow = dummyWidget;

  stack->addWidget(containerWindow);
  stack->addWidget(dummyWidget);
  layout->addWidget(navigationWindow);
  layout->addWidget(stack);
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

// A placeholder too
void MainWindow::handleContainerClicked() {
  // TODO: something
  qDebug() << "Clicked a Container!\n";
  stack->setCurrentWidget(openContainerWindow);
}

void MainWindow::handleBackButton() {
  qDebug() << "Clicked back form a container\n";
  stack->setCurrentWidget(containerWindow);
}
