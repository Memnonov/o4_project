// Copyright [2025] Auli Jussila & Mikko Memonen

#include "../include/o4_project/navigation_panel.h"
#include <QSize>
#include <QSizePolicy>
#include <QtLogging>
#include <qicon.h>
#include <qlogging.h>
#include <qpushbutton.h>

const QMap<NavigationPanel::NavAction, QString>
    NavigationPanel::navActionMap = {
        {NavigationPanel::NavAction::BrowseItems, "Browse Items"},
        {NavigationPanel::NavAction::SearchItems, "Search Items"},
        {NavigationPanel::NavAction::MoveItems, "Move Items"},
        {NavigationPanel::NavAction::Tutorial, "Tutorial"},
        {NavigationPanel::NavAction::About, "About"},
        {NavigationPanel::NavAction::Quit, "Quit"}};

NavigationPanel::NavigationPanel(QWidget *parent)
    : QFrame{parent}, layout{new QVBoxLayout{this}}, logo(new QLabel),
      buttons{new QButtonGroup{this}} {
  setObjectName("NavigationPanel");
  setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
  layout->setSpacing(24); // TODO(mikko): separate styling to qss?

  initLogo();
  initButtons();
  layout->addStretch();
}

void NavigationPanel::initLogo() {
  logo->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  QPixmap logoPixMap{":/logo/ai_logo.png"};
  if (logoPixMap.isNull()) {
    qDebug() << "couldn't load image!\n";
  }
  logo->setPixmap(logoPixMap.scaled(200, 200, Qt::KeepAspectRatio));
  logo->setAlignment(Qt::AlignCenter);
  layout->addWidget(logo);
}

void NavigationPanel::initButtons() {
  buttons->setExclusive(true);
  for (const auto &key : NavigationPanel::navActionMap.keys()) {
    createButton(key);
  }
}

void NavigationPanel::setSelection(NavigationPanel::NavAction action) {
  using NavAction = NavigationPanel::NavAction;
  auto button = this->findChild<QPushButton*>(navActionToString(action));
  if (button) {
    button->setChecked(true);
  }
}

void NavigationPanel::createButton(NavAction action) {
  auto button = new QPushButton(navActionToString(action));
  buttons->addButton(button);
  button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  button->setCheckable(true);
  button->setIcon(getNavIcon(action));
  button->setObjectName(navActionToString(action));
  if (action == NavigationPanel::NavAction::BrowseItems) {
    button->setChecked(true);
  }
  connect(button, &QPushButton::clicked, this,
          [this, action]() { emit buttonPressed(action); });
  layout->addWidget(button);
}

QString NavigationPanel::navActionToString(NavAction action) {
  return NavigationPanel::navActionMap.value(action, "");
}

QIcon NavigationPanel::getNavIcon(NavAction action) {
  using NavAction = NavigationPanel::NavAction;
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
