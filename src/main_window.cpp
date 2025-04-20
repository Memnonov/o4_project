// Copyright [2025] Auli Jussila & Mikko Memonen

#include "../include/o4_project/main_window.h"
#include "../include/o4_project/items_window.h"
#include "../include/o4_project/navigation_window.h"
#include "container_window.h"
#include "item_info_window.h"
#include <QApplication>
#include <QHBoxLayout>
#include <QStackedWidget>
#include <QtLogging>
#include <qapplication.h>
#include <qboxlayout.h>
#include <qframe.h>
#include <qlabel.h>
#include <qlogging.h>
#include <qpushbutton.h>
#include <qsizepolicy.h>
#include <qstackedwidget.h>
#include <qwidget.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), navigationWindow{new NavigationWindow},
      containerWindow{new ContainerWindow}, leftStack{new QStackedWidget},
      rightStack{new QStackedWidget}, itemsWindow{new ItemsWindow},
      infoWindow{new ItemInfoWindow} {
  QWidget *central = new QWidget(this);
  QHBoxLayout *layout = new QHBoxLayout(central);
  setCentralWidget(central);

  connect(navigationWindow, &NavigationWindow::buttonPressed, this,
          &MainWindow::handleNavigation);
  connect(containerWindow, &ContainerWindow::containerSelected, this,
          &MainWindow::handleContainerClicked);
  connect(itemsWindow, &ItemsWindow::itemsWindowClosed, this,
          &MainWindow::handleBackButton);
  connect(itemsWindow, &ItemsWindow::itemSelected, infoWindow,
          &ItemInfoWindow::updateItem);

  // Wrap inside a frame to pop!
  leftWindowFrame = new QFrame;
  rightWindowFrame = new QFrame;
  for (auto frame : {leftWindowFrame, rightWindowFrame}) {
    frame->setFrameShape(QFrame::StyledPanel);
    frame->setFrameShadow(QFrame::Sunken);
  }
  auto leftWindowFrameLayout = new QVBoxLayout;
  leftWindowFrameLayout->addWidget(leftStack);
  leftWindowFrame->setLayout(leftWindowFrameLayout);
  auto rightWindowFrameLayout = new QVBoxLayout;
  rightWindowFrameLayout->addWidget(rightStack);
  rightWindowFrame->setLayout(rightWindowFrameLayout);

  auto dummyA = new ContainerWindow;
  auto dummyB = new ContainerWindow;
  auto dummyC = new ContainerWindow;
  // auto dummyWidget = new QWidget;
  // auto dummyLayout = new QVBoxLayout;
  // dummyLayout->addWidget(new QLabel{"Dummy!"});
  // auto backButton = new QPushButton{"Back"};
  // connect(backButton, &QPushButton::clicked, this,
  // &MainWindow::handleBackButton); dummyLayout->addWidget(backButton);
  // dummyWidget->setLayout(dummyLayout);

  leftStack->addWidget(containerWindow);
  leftStack->addWidget(itemsWindow);
  rightStack->addWidget(infoWindow);

  layout->addWidget(navigationWindow);
  layout->addWidget(leftWindowFrame);
  layout->addWidget(rightWindowFrame);

  layout->setStretch(0, 1);
  layout->setStretch(1, 2);
  layout->setStretch(2, 2);
}

// A placeholder for actual behaviour.
void MainWindow::handleNavigation(NavigationWindow::NavAction action) {
  qDebug() << "Pressed navigation button: "
           << NavigationWindow::navActionToString(action);
  switch (action) {
  case NavigationWindow::NavAction::Quit:
    QApplication::quit();
  default:
    break;
  }
}

// A placeholder too
void MainWindow::handleContainerClicked() {
  // TODO: something
  qDebug() << "Clicked a Container!\n";
  leftStack->setCurrentWidget(itemsWindow);
}

void MainWindow::handleBackButton() {
  qDebug() << "Clicked back form a container\n";
  leftStack->setCurrentWidget(containerWindow);
  infoWindow->updateItem();
}
