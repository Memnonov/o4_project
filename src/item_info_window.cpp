// Copyright [2025] Auli Jussila & Mikko Memonen

#include "../include/o4_project/item_info_window.h"
#include <QStringList>
#include <qnamespace.h>
#include <qsizepolicy.h>

ItemInfoWindow::ItemInfoWindow(QWidget *parent)
    : title{new QLabel}, layout{new QVBoxLayout{this}},
      tip{new QLabel{"Select a container from the left to browse items."}},
      topPanel{new QWidget}, editButton{new QPushButton} {
  layout->setAlignment(Qt::AlignTop);
  
  title->setText(QString("<b>%1</b>").arg(itemName));
  topPanel->setLayout(new QHBoxLayout);
  title->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  editButton->setFlat(true);
  editButton->setCheckable(true);
  editButton->setIcon(QIcon(":/icons/edit-pencil.svg"));
  
  topPanel->layout()->addWidget(title);
  topPanel->layout()->addWidget(editButton);
  
  layout->addWidget(topPanel);
  
  tip->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  initViewFields();
  layout->addWidget(tip);
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
  viewDescriptionLabel->setSizePolicy(QSizePolicy::Preferred,
                                      QSizePolicy::Expanding);
  viewDescriptionLabel->setAlignment(Qt::AlignTop);
  descriptionScrollArea->setWidget(viewDescriptionLabel);
  descriptionScrollArea->setWidgetResizable(true);
  descriptionScrollArea->setAlignment(Qt::AlignTop);
  descriptionScrollArea->setSizePolicy(QSizePolicy::Preferred,
                                       QSizePolicy::Expanding);
  viewFormLayout->addRow("Name: ", viewNameLabel);
  viewFormLayout->addRow("Quantity: ", viewQuantityLabel);
  viewFormLayout->addRow("Tags:", viewTagsLabel);

  viewBox->addLayout(viewFormLayout);
  viewBox->addSpacing(20);
  viewBox->addWidget(new QLabel{"Description:"});
  viewBox->addWidget(descriptionScrollArea);
  layout->addWidget(viewFields);
  updateItem(); // TODO: Don't use the dummy!
}

void ItemInfoWindow::updateItem(Item *selectedItem) {
  this->item = selectedItem;
  if (item) {
    title->setText(QString("<b>%1</b>").arg(item->name));
    viewNameLabel->setText(item->name);
    viewQuantityLabel->setText(QString::number(item->quantity));
    viewTagsLabel->setText(QStringList::fromVector(item->tags).join(", "));
    viewDescriptionLabel->setText(item->description);
    viewFields->setVisible(true);
    tip->setVisible(false);
    editButton->setVisible(true);
    return;
  }
  title->setText("<b>Item info</b>");
  title->setAlignment(Qt::AlignVCenter);
  viewNameLabel->setText("null");
  viewQuantityLabel->setText("null");
  viewTagsLabel->setText("null");
  viewDescriptionLabel->setText("null");
  viewFields->setVisible(false);
  tip->setVisible(true);
  editButton->setVisible(false);
}
