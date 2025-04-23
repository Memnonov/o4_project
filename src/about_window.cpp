#include "../include/o4_project/about_window.h"

AboutWindow::AboutWindow(QWidget *parent)
    : ModeFrame{parent}, placeholder(new QLabel{"Something about the app."}) {
  layout->setAlignment(Qt::AlignCenter);
  layout->addWidget(placeholder);
}
