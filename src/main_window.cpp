// Copyright [2025] Auli Jussila & Mikko Memonen

#include "../include/o4_project/main_window.h"
#include "../include/o4_project/navigation_window.h"
#include <QHBoxLayout>
#include <qboxlayout.h>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  QWidget *central = new QWidget(this);
  QHBoxLayout *layout = new QHBoxLayout(central);
  setCentralWidget(central);

  layout->addWidget(new NavigationWindow(this));
  layout->addWidget(new QLabel("PLACEHOLDER 2", central));
  layout->addWidget(new QLabel("PLACEHOLDER 3", central));
}
