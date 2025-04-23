// Copyright [2025] Auli Jussila & Mikko Memonen

#include "../include/o4_project/main_window.h"
#include "../include/o4_project/items_window.h"
#include "../include/o4_project/navigation_window.h"
#include "container_window.h"
#include "item_info_window.h"
#include "search_window.h"
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
    : QMainWindow{parent}, mainStack{new QStackedWidget},
      browseWindow{new BrowseWindow}, navigationWindow{new NavigationWindow},
      containerWindow{new ContainerWindow}, leftStack{new QStackedWidget},
      rightStack{new QStackedWidget}, itemsWindow{new ItemsWindow},
      infoWindow{new ItemInfoWindow}, searchWindow{new SearchWindow} {
  auto *central = new QWidget(this);
  auto *layout = new QHBoxLayout(central);
  setCentralWidget(central);

  connect(navigationWindow, &NavigationWindow::buttonPressed, this,
          &MainWindow::handleNavigation);

  mainStack->addWidget(browseWindow);
  mainStack->addWidget(searchWindow);
  layout->addWidget(navigationWindow);
  layout->addWidget(mainStack);

  layout->setStretch(0, 1);
  layout->setStretch(1, 4);
}

// A placeholder for actual behaviour.
void MainWindow::handleNavigation(NavigationWindow::NavAction action) {
  using NavAction = NavigationWindow::NavAction;
  qDebug() << "Pressed navigation button: "
           << NavigationWindow::navActionToString(action);
  switch (action) {
  case NavAction::BrowseItems:
    mainStack->setCurrentWidget(browseWindow);
    break;
  case NavAction::SearchItems:
    mainStack->setCurrentWidget(searchWindow);
    break;
  case NavAction::Quit:
    QApplication::quit();
  default:
    break;
  }
}
