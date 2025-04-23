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
    : QMainWindow(parent), mainStack{new QStackedWidget},
      browseWindow(new QWidget), navigationWindow{new NavigationWindow},
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

  leftStack->addWidget(wrapInFrame(containerWindow));
  leftStack->addWidget(itemsWindow);
  rightStack->addWidget(infoWindow);
  auto browseLayout = new QHBoxLayout;
  browseWindow->setLayout(browseLayout);
  browseWindow->layout()->addWidget(leftStack);
  browseWindow->layout()->addWidget(rightStack);
  browseLayout->setStretch(0, 1);
  browseLayout->setStretch(1, 1);
  layout->addWidget(navigationWindow);
  layout->addWidget(wrapInFrame(browseWindow));
  // layout->addWidget(leftWindowFrame);
  // layout->addWidget(rightWindowFrame);

  layout->setStretch(0, 1);
  layout->setStretch(1, 4);
}

QWidget *MainWindow::wrapInFrame(QWidget *inner) {
  if (!inner) {
    qWarning() << "wrapInframe was given a nullptr";
    return nullptr;
  }
  auto frame = new QFrame;
  frame->setFrameShape(QFrame::StyledPanel);
  frame->setLayout(new QHBoxLayout);
  frame->layout()->addWidget(inner);
  return frame;
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
