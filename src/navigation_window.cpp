// Copyright [2025] Auli Jussila & Mikko Memonen

#include "../include/o4_project/navigation_window.h"
#include <QSize>
#include <QSizePolicy>
#include <QtLogging>
#include <qicon.h>

const QMap<NavigationWindow::NavAction, QString>
    NavigationWindow::navActionMap = {
        {NavigationWindow::NavAction::BrowseItems, "Browse Items"},
        {NavigationWindow::NavAction::SearchItems, "Search Items"},
        {NavigationWindow::NavAction::MoveItems, "Move Items"},
        {NavigationWindow::NavAction::Tutorial, "Tutorial"},
        {NavigationWindow::NavAction::About, "About"},
        {NavigationWindow::NavAction::Quit, "Quit"}};

NavigationWindow::NavigationWindow(QWidget *parent)
    : QFrame{parent}, layout{new QVBoxLayout{this}}, logo(new QLabel),
      buttons{new QButtonGroup{this}} {
  setObjectName("NavigationWindow");
  setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
  layout->setSpacing(24); // TODO(mikko): separate styling to qss?

  initLogo();
  initButtons();
  layout->addStretch();
}

void NavigationWindow::initLogo() {
  logo->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  QPixmap logoPixMap{":/logo/ai_logo.png"};
  if (logoPixMap.isNull()) {
    qDebug() << "couldn't load image!\n";
  }
  logo->setPixmap(logoPixMap.scaled(200, 200, Qt::KeepAspectRatio));
  logo->setAlignment(Qt::AlignCenter);
  layout->addWidget(logo);
}

void NavigationWindow::initButtons() {
  buttons->setExclusive(true);
  for (const auto &key : NavigationWindow::navActionMap.keys()) {
    createButton(key);
  }
}

void NavigationWindow::createButton(NavAction action) {
  auto button = new QPushButton(navActionToString(action));
  buttons->addButton(button);
  button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  button->setCheckable(true);
  button->setIcon(getNavIcon(action));
  if (action == NavigationWindow::NavAction::BrowseItems) {
    button->setChecked(true);
  }
  connect(button, &QPushButton::clicked, this,
          [this, action]() { emit buttonPressed(action); });
  layout->addWidget(button);
}

QString NavigationWindow::navActionToString(NavAction action) {
  return NavigationWindow::navActionMap.value(action, "");
}

QIcon NavigationWindow::getNavIcon(NavAction action) {
  using NavAction = NavigationWindow::NavAction;
  switch (action) {
  case NavAction::BrowseItems: {
    return QIcon{":/icons/eye.svg"};
  }
  case NavAction::MoveItems: {
    return QIcon{":/icons/arrow-separate.svg"};
  }
  case NavAction::SearchItems: {
    return QIcon{":/icons/search.svg"};
  }
  case NavAction::Tutorial: {
    return QIcon{":/icons/book.svg"};
  }
  case NavAction::About: {
    return QIcon{":/icons/help-square.svg"};
  }
  case NavAction::Quit: {
    return QIcon{":/icons/log-out.svg"};
  }
  default:
    return QIcon();
  }
}
