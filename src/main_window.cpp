// Copyright [2025] Auli Jussila & Mikko Memonen

#include "../include/o4_project/main_window.h"
#include "about_window.h"
#include "browse_window.h"
#include <QApplication>
#include <QHBoxLayout>
#include <QStackedWidget>
#include <QtLogging>
#include <qapplication.h>
#include <qboxlayout.h>
#include <qframe.h>
#include <qlabel.h>
#include <qlogging.h>
#include <qobject.h>
#include <qpushbutton.h>
#include <qsizepolicy.h>
#include <qstackedwidget.h>
#include <qwidget.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}, model{new ContainerModel{this}}, searchModel{new SearchModel{model, this}},
      statusBar{new StatusBar}, mainStack{new QStackedWidget},
      aboutWindow{new AboutWindow}, tutorialWindow{new TutorialWindow},
      moveWindow{new MoveWindow{model}}, browseWindow{new BrowseWindow{model}},
      mainArea{new QWidget}, navigationPanel{new NavigationPanel},
      containerWindow{new ContainerWindow{model}},
      leftStack{new QStackedWidget}, rightStack{new QStackedWidget},
      itemsWindow{new ItemsWindow}, infoWindow{new ItemInfoWindow},
      searchWindow{new SearchWindow{model, searchModel}} {
  qRegisterMetaType<Item *>("Item*");

  model->initDefaultInventory();
  browseWindow->refresh();
  moveWindow->refresh();
  searchModel->refresh();
  searchWindow->refresh();

  auto *central = new QWidget(this);
  auto *layout = new QHBoxLayout(central);
  setCentralWidget(central);

  initConnections();
  layout->addWidget(navigationPanel);
  initMainArea();

  layout->addWidget(mainArea);

  layout->setStretch(0, 1);
  layout->setStretch(1, 4);
}

void MainWindow::initMainArea() {
  mainArea->setLayout(new QVBoxLayout);
  mainArea->layout()->addWidget(statusBar);
  mainArea->layout()->addWidget(mainStack);
  mainStack->addWidget(browseWindow);
  mainStack->addWidget(searchWindow);
  mainStack->addWidget(moveWindow);
  mainStack->addWidget(tutorialWindow);
  mainStack->addWidget(aboutWindow);
}

void MainWindow::initConnections() {
  connect(navigationPanel, &NavigationPanel::buttonPressed, this,
          &MainWindow::handleNavigation);
  connect(statusBar, &StatusBar::undoClicked, model,
          &ContainerModel::handleUndo);
  connect(statusBar, &StatusBar::redoClicked, model,
          &ContainerModel::handleRedo);
  connect(model, &ContainerModel::modelChanged, browseWindow,
          &BrowseWindow::refresh);
  connect(model, &ContainerModel::modelChanged, moveWindow,
          &MoveWindow::refresh);
  connect(model, &ContainerModel::modelChanged, statusBar,
          &StatusBar::updateStatus);
}

void MainWindow::handleNavigation(NavigationPanel::NavAction action) {
  using NavAction = NavigationPanel::NavAction;
  qDebug() << "Pressed navigation button: "
           << NavigationPanel::navActionToString(action);
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
