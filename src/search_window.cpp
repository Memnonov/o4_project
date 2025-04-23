#include "../include/o4_project/search_window.h"

SearchWindow::SearchWindow(QWidget *parent)
    : ModeFrame{parent}, placeholder(new QLabel{"Search window here!"}) {
  layout->setAlignment(Qt::AlignCenter);
  layout->addWidget(placeholder);
}
