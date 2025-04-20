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

  viewNameLabel = new QLabel;
  viewQuantityLabel = new QLabel;
  viewTagsLabel = new QLabel;
  auto descriptionScrollArea = new QScrollArea;
  viewDescriptionLabel = new QLabel;
  viewDescriptionLabel->setWordWrap(true);
  descriptionScrollArea->setWidget(viewDescriptionLabel);
  descriptionScrollArea->setWidgetResizable(true);
  viewFormLayout->addRow("Name: ", viewNameLabel);
  viewFormLayout->addRow("Quantity: ", viewQuantityLabel);
  viewFormLayout->addRow("Tags:", viewTagsLabel);

  viewBox->addLayout(viewFormLayout);
  viewBox->addWidget(new QLabel{"Description:"});
  viewBox->addWidget(descriptionScrollArea);
  layout->addWidget(viewFields);
  updateItem(); // TODO: Don't use the dummy!
}

void ItemInfoWindow::updateItem(Item *selectedItem) {
  this->item = selectedItem;
  if (item) {
    viewNameLabel->setText(item->name);
    viewQuantityLabel->setText(QString::number(item->quantity));
    viewTagsLabel->setText(QStringList::fromVector(item->tags).join(", "));
    viewDescriptionLabel->setText(item->description);
    return;
  }
  viewNameLabel->setText("null");
  viewQuantityLabel->setText("null");
  viewTagsLabel->setText("null");
  viewDescriptionLabel->setText("null");
}
