#include "../include/o4_project/about_window.h"
#include <qnamespace.h>

AboutWindow::AboutWindow(QWidget *parent)
    : ModeFrame{parent}, placeholder(new QLabel{"Something about the app."}) {
  setObjectName("AboutWindow");
  layout->setAlignment(Qt::AlignCenter);
  layout->addWidget(placeholder);
  placeholder->setAlignment(Qt::AlignCenter);
  QString text(R"(
<b>Treasure Hoard</b><br><br>
Should be a good enough tabletop rpg inventory management app.<br>
Made by Auli Jussila & Mikko Memonen for the course Ohjelmointi 4, 2025.<br>
Made with Qt6.<br><br>
Icons from iconoir.com
   )");
  placeholder->setText(text);
}
