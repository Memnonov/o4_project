// Copyright [2025] Auli Jussila & Mikko Memonen

#include "../include/o4_project/main_window.h"
#include "about_window.h"
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
      aboutWindow{new AboutWindow}, tutorialWindow{new TutorialWindow},
      moveWindow{new MoveWindow}, browseWindow{new BrowseWindow},
      navigationWindow{new NavigationWindow},
      containerWindow{new ContainerWindow}, leftStack{new QStackedWidget},
      rightStack{new QStackedWidget}, itemsWindow{new ItemsWindow},
      infoWindow{new ItemInfoWindow}, searchWindow{new SearchWindow} {
  auto *central = new QWidget(this);
  auto *layout = new QHBoxLayout(central);
  setCentralWidget(central);

  connect(navigationWindow, &NavigationWindow::buttonPressed, this,
          &MainWindow::handleNavigation);
  layout->addWidget(navigationWindow);
  initMainStack();
  layout->addWidget(mainStack);

  layout->setStretch(0, 1);
  layout->setStretch(1, 4);
}

void MainWindow::initMainStack() {
  mainStack->addWidget(browseWindow);
  mainStack->addWidget(searchWindow);
  mainStack->addWidget(moveWindow);
  mainStack->addWidget(tutorialWindow);
  mainStack->addWidget(aboutWindow);
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
  case NavAction::MoveItems:
    mainStack->setCurrentWidget(moveWindow);
    break;
  case NavAction::Tutorial:
    mainStack->setCurrentWidget(tutorialWindow);
    break;
  case NavAction::About:
    mainStack->setCurrentWidget(aboutWindow);
    break;
  case NavAction::Quit:
    QApplication::quit();
  default:
    break;
  }
}
