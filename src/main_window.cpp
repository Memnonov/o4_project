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
#include <qtmetamacros.h>
#include <qwidget.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}, centralWidget(new QWidget{this}),
      model{new ContainerModel{this}},
      searchProxyModel{new SearchProxyModel{this}},
      searchModel{new SearchModel{model, this}}, statusBar{new StatusBar},
      mainStack{new QStackedWidget}, aboutWindow{new AboutWindow},
      tutorialWindow{new TutorialWindow}, moveWindow{new MoveWindow{model}},
      browseWindow{new BrowseWindow{model}}, mainArea{new QWidget},
      navigationPanel{new NavigationPanel},
      containerWindow{new ContainerWindow{model}}, itemsWindow{new ItemsWindow},
      infoWindow{new ItemInfoWindow},
      searchWindow{new SearchWindow{model, searchModel, searchProxyModel}} {
  qRegisterMetaType<Item *>("Item*");
  setCentralWidget(centralWidget);
  auto *layout = new QHBoxLayout(centralWidget);
  model->initDefaultInventory();
  layout->addWidget(navigationPanel);

  initMainArea();
  layout->addWidget(mainArea);
  layout->setStretch(0, 1);
  layout->setStretch(1, 4);

  initConnections();
  browseWindow->refresh();
  moveWindow->refresh();
  searchModel->refresh();
  searchWindow->refresh();
  setNames();
  dumpParents();
}

void MainWindow::initMainArea() {
  mainArea->setLayout(new QVBoxLayout{mainArea});
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
  connect(model, &ContainerModel::modelChanged, searchWindow,
          &SearchWindow::refresh);

  connect(searchWindow, &SearchWindow::goToItemClicked, this,
          &MainWindow::handleGoToItem);
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
    searchWindow->refit();
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

void MainWindow::handleGoToItem(Item *item, Container *container) {
  browseWindow->handleGoToItem(item, container);
  handleNavigation(NavigationPanel::NavAction::BrowseItems);
  navigationPanel->setSelection(NavigationPanel::NavAction::BrowseItems);
}

void MainWindow::setNames() {
  setObjectName("MainWindow");
  centralWidget->setObjectName("CentralWidget");
  mainStack->setObjectName("MainStack");
  mainArea->setObjectName("MainArea");
}

// Ensure hierarchy
void MainWindow::setParents() {
  statusBar->setParent(mainArea);
  mainStack->setParent(mainArea);
}

// For debugging.
void MainWindow::dumpParents() {
  QVector<QObject *> objects = {
      model,           searchProxyModel, searchModel,    centralWidget,
      containerWindow, itemsWindow,      infoWindow,     searchWindow,
      navigationPanel, mainArea,         tutorialWindow, aboutWindow,
      mainStack};
  for (auto object : objects) {
    if (!object) {
      return;
    }
    qDebug() << "Name:" << object->objectName() << " : Parent:"
             << (object->parent() ? object->parent()->objectName() : "null");
  }
}
