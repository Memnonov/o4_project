// Copyright [2025] Auli Jussila & Mikko Memonen

#include "../include/o4_project/main_window.h"
#include "../include/o4_project/navigation_window.h"
#include <QHBoxLayout>
#include <QtLogging>
#include <qboxlayout.h>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  QWidget *central = new QWidget(this);
  QHBoxLayout *layout = new QHBoxLayout(central);
  setCentralWidget(central);

  connect(&navigationWindow, &NavigationWindow::buttonPressed, this,
          &MainWindow::handleNavigation);

  layout->addWidget(&navigationWindow);
  layout->addWidget(new QLabel("PLACEHOLDER 2", central));
  layout->addWidget(new QLabel("PLACEHOLDER 3", central));
}

// A placeholder for actual behaviour.
void MainWindow::handleNavigation(NavigationWindow::NavAction action) {
  qDebug() << "Pressed navigation button: "
           << NavigationWindow::navActionToString(action);
}
