#include "../include/o4_project/status_bar.h"
#include <qlogging.h>
#include <qnamespace.h>
#include <qpushbutton.h>

StatusBar::StatusBar(QWidget *parent)
    : QWidget(parent), statusMessage{new QLabel}, undoButton{new QPushButton},
      redoButton{new QPushButton} {
  auto layout = new QHBoxLayout{this};
  layout->setAlignment(Qt::AlignRight);
  
  statusMessage->setText("<i>This here is gonna be a status bar</i>");
  undoButton->setIcon(QIcon(":/icons/undo.svg"));
  redoButton->setIcon(QIcon(":/icons/redo.svg"));
  undoButton->setFlat(true);
  redoButton->setFlat(true);

  layout->addStretch();
  layout->addWidget(statusMessage);
  layout->addStretch();
  layout->addWidget(undoButton);
  layout->addWidget(redoButton);

}
