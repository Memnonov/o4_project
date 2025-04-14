// Copyright [2025] Auli Jussila & Mikko Memonen

#include "../include/o4_project/navigation_window.h"
#include <qpushbutton.h>

NavigationWindow::NavigationWindow(QWidget *parent)
    : QWidget(parent), layout(new QVBoxLayout(this)) {
  for (const auto& button : buttons) {
    addButton(button);
  }
}

void NavigationWindow::addButton(const QString& label) {
  QPushButton *button = new QPushButton(label);
  layout->addWidget(button);
}
