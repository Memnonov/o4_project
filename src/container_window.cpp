#include "../include/o4_project/container_window.h"
#include <qboxlayout.h>
#include <qlabel.h>
#include <qnamespace.h>
#include <QPushButton>
#include <qscrollarea.h>
#include <qsizepolicy.h>
#include <qwidget.h>

ContainerWindow::ContainerWindow(QWidget *parent)
    : QFrame{parent}, layout{new QVBoxLayout{this}},
      scrollArea{new QScrollArea{this}} {
  
  setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  QLabel *containersLabel = new QLabel{"Containers"};
  containersLabel->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
  layout->addWidget(containersLabel);
  
  QWidget *rowsWidget = new QWidget;
  QVBoxLayout *rows = new QVBoxLayout{rowsWidget};
  for (unsigned int i = 0; i < 18; ++i) {
    QPushButton *button = new QPushButton{"Junk Button"};
    button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    rows->addWidget(button);
  }
  scrollArea->setWidgetResizable(true);
  scrollArea->setWidget(rowsWidget);
  layout->addWidget(scrollArea);
}
