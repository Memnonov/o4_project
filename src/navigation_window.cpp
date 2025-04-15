// Copyright [2025] Auli Jussila & Mikko Memonen

#include "../include/o4_project/navigation_window.h"
#include <QSizePolicy>
#include <qpushbutton.h>
#include <qsizepolicy.h>
#include <qtmetamacros.h>

const QMap<NavigationWindow::NavAction, QString>
    NavigationWindow::navActionMap = {
        {NavigationWindow::NavAction::BrowseItems, "Browse Items"},
        {NavigationWindow::NavAction::SearchItems, "Search Items"},
        {NavigationWindow::NavAction::MoveItems, "Move Items"},
        {NavigationWindow::NavAction::Tutorial, "Tutorial"},
        {NavigationWindow::NavAction::About, "About"},
        {NavigationWindow::NavAction::Quit, "Quit"}};

QString NavigationWindow::navActionToString(NavAction action) {
  return NavigationWindow::navActionMap.value(action, "");
}

NavigationWindow::NavigationWindow(QWidget *parent)
    : QWidget(parent), layout(new QVBoxLayout(this)) {
  layout->setSpacing(24);  // TODO(mikko): separate styling to qss
  layout->addStretch();
  for (const auto &action : NavigationWindow::navActionMap.keys()) {
    addButton(action);
  }
  layout->addStretch();
}

void NavigationWindow::addButton(NavAction action) {
  QPushButton *button = new QPushButton(navActionToString(action));
  button->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
  connect(button, &QPushButton::clicked, this,
          [this, action]() { emit buttonPressed(action); });
  layout->addWidget(button);
}
