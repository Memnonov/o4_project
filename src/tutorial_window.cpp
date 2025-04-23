#include "../include/o4_project/tutorial_window.h"

TutorialWindow::TutorialWindow(QWidget *parent)
    : ModeFrame{parent}, placeholder(new QLabel{"Tutorial here! Getting learnt!"}) {
  layout->setAlignment(Qt::AlignCenter);
  layout->addWidget(placeholder);
}
