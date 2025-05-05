#include "../include/o4_project/status_bar.h"
#include <algorithm>
#include <qlogging.h>
#include <qnamespace.h>
#include <qpushbutton.h>
#include <qsizepolicy.h>
#include <qtmetamacros.h>

StatusBar::StatusBar(QWidget *parent)
    : QWidget(parent), statusMessage{new QLabel}, undoButton{new QPushButton},
      redoButton{new QPushButton} {
  setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
  setContentsMargins(0, 0, 0, 0);
  auto layout = new QHBoxLayout{this};
  initUndoButtons();
  
  layout->setContentsMargins(0, 0, 0, 0);
  layout->setAlignment(Qt::AlignRight);
  statusMessage->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
  statusMessage->setText("<i>This here is gonna be a status bar</i>");

  layout->addStretch();
  layout->addWidget(statusMessage);
  layout->addStretch();
  layout->addWidget(undoButton);
  layout->addWidget(redoButton);
}

void StatusBar::initUndoButtons() {
  for (auto button : {undoButton, redoButton}) {
  button->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
  button->setFlat(true);
  }
  undoButton->setIcon(QIcon(":/icons/undo.svg"));
  redoButton->setIcon(QIcon(":/icons/redo.svg"));
  connect(undoButton, &QPushButton::clicked, this, [this] () {
    emit undoClicked();
  });
  connect(redoButton, &QPushButton::clicked, this, [this] () {
    emit redoClicked();
  });
}

void StatusBar::updateStatus(QString message) {
  statusMessage->setText(message);
}
