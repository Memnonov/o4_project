// Copyright [2025] Auli Jussila & Mikko Memonen

#include "../include/o4_project/item_info_window.h"

ItemInfoWindow::ItemInfoWindow(QWidget *parent)
    : title{new QLabel}, layout{new QVBoxLayout{this}} {
  title->setText(QString("<b>%1</b>").arg(itemName));
  layout->addWidget(title);
  layout->addStretch();
}


