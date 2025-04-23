#include "../include/o4_project/move_window.h"

MoveWindow::MoveWindow(QWidget *parent)
    : ModeFrame{parent}, placeholder{new QLabel{"Move items here!"}} {
  layout->setAlignment(Qt::AlignCenter);
  layout->addWidget(placeholder);
}
