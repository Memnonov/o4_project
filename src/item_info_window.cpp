// Copyright [2025] Auli Jussila & Mikko Memonen

#include "../include/o4_project/item_info_window.h"
#include <QStringList>

ItemInfoWindow::ItemInfoWindow(QWidget *parent)
    : title{new QLabel}, layout{new QVBoxLayout{this}} {
  title->setText(QString("<b>%1</b>").arg(itemName));
  layout->addWidget(title);
  initViewFields();
  layout->addStretch();
}

void ItemInfoWindow::initViewFields() {
  viewFields = new QWidget;
  auto viewBox = new QVBoxLayout{viewFields};
  auto viewFormLayout = new QFormLayout;

  
  auto name = new QLabel{itemName};
  auto quantity = new QLabel{"itemQuantity"};
  auto tags = new QLabel{QStringList::fromVector(itemTags).join(", ")};
  auto descriptionScrollArea = new QScrollArea;
  auto description = new QLabel{itemDescription};
  description->setWordWrap(true);
  descriptionScrollArea->setWidget(description);
  descriptionScrollArea->setWidgetResizable(true);
  viewFormLayout->addRow("Name: ", name);
  viewFormLayout->addRow("Quantity: ", quantity);
  viewFormLayout->addRow("Tags:", tags);

  viewBox->addLayout(viewFormLayout);
  viewBox->addWidget(new QLabel{"Description:"});
  viewBox->addWidget(descriptionScrollArea);
  layout->addWidget(viewFields);
}
