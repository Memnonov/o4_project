// Copyright [2025] Auli Jussila & Mikko Memonen

#include "../include/o4_project/navigation_window.h"
#include <QSizePolicy>
#include <qframe.h>
#include <qlabel.h>
#include <qlogging.h>
#include <qnamespace.h>
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

NavigationWindow::NavigationWindow(QWidget *parent)
    : QFrame(parent), layout(new QVBoxLayout(this)) {
  setObjectName("NavigationWindow");
  layout->setSpacing(24);  // TODO(mikko): separate styling to qss
  layout->addStretch();

  logoLabel = new QLabel(this);
  QPixmap logoPixMap{"assets/ai_logo.png"};
  if (logoPixMap.isNull()) {
    qDebug() << "couldn't load image!\n";
  }
  logoLabel->setPixmap(logoPixMap.scaledToHeight(height() / 3));
  logoLabel->setAlignment(Qt::AlignCenter);
  layout->addWidget(logoLabel);

  for (const auto &action : NavigationWindow::navActionMap.keys()) {
    addButton(action);
  }
  layout->addStretch();

  // TODO(mikko): Use a qss file.
  setStyleSheet("QWidget#NavigationWindow { border: 1px solid #000000; "
                "border-radius: 8px; "
                "padding: 10px; }");
}

QString NavigationWindow::navActionToString(NavAction action) {
  return NavigationWindow::navActionMap.value(action, "");
}

void NavigationWindow::addButton(NavAction action) {
  QPushButton *button = new QPushButton(navActionToString(action));
  button->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
  connect(button, &QPushButton::clicked, this,
          [this, action]() { emit buttonPressed(action); });
  layout->addWidget(button);
}
