#include "../include/o4_project/about_window.h"
#include <qnamespace.h>

AboutWindow::AboutWindow(QWidget *parent)
    : ModeFrame{parent}, placeholder(new QLabel{"Something about the app."}) {
  layout->setAlignment(Qt::AlignCenter);
  layout->addWidget(placeholder);
  placeholder->setAlignment(Qt::AlignCenter);
  placeholder->setText(R"(
                       Should be a good enough tabletop rpg inventory management app.
                       Made by Auli Jussila & Mikko Memonen for the course Ohjelmointi 4, 2025.
                       Made with Qt6.
                       Icons from iconoir.com
                       )");
}
