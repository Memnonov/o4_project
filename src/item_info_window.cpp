// Copyright [2025] Auli Jussila & Mikko Memonen

#include "../include/o4_project/item_info_window.h"
#include <QLineEdit>
#include <QStringList>
#include <QSpinBox>
#include <QTextEdit>
#include <qlogging.h>
#include <qnamespace.h>
#include <qsizepolicy.h>
#include <qtextedit.h>

ItemInfoWindow::ItemInfoWindow(QWidget *parent)
    : title{new QLabel}, layout{new QVBoxLayout{this}},
      tip{new QLabel{"Select a container from the left to browse items."}},
      topPanel{new QWidget}, editButton{new QPushButton} {
  layout->setAlignment(Qt::AlignTop);

  title->setText(QString("<b>%1</b>").arg(itemName));
  topPanel->setLayout(new QHBoxLayout);
  title->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  initEditButton();
  topPanel->layout()->addWidget(title);
  topPanel->layout()->addWidget(editButton);

  layout->addWidget(topPanel);

  tip->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  initViewFields();
  initEditFields();
  updateItem();
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
}

// Not very dry here...
void ItemInfoWindow::initEditFields() {
  editFields = new QWidget;
  auto editBox = new QVBoxLayout{editFields};
  auto editFormLayout = new QFormLayout;

  editNameLabel = new QLineEdit;
  editNameLabel->setPlaceholderText("Item name");
  editNameLabel->setText(item ? item->name : "");
  editQuantityBox = new QSpinBox;
  editQuantityBox->setMaximum(9999);
  editQuantityBox->setValue(item ? item->quantity : 0);
  editTagsLabel = new QLineEdit;
  editTagsLabel->setPlaceholderText("Separate tags with #: #tag1 #tag2 #tag3");
  auto descriptionScrollArea = new QScrollArea;
  editDescriptionLabel = new QTextEdit;
  editDescriptionLabel->setPlaceholderText("Write item description here.");
  editDescriptionLabel->setLineWrapMode(QTextEdit::WidgetWidth);
  editDescriptionLabel->setSizePolicy(QSizePolicy::Preferred,
                                      QSizePolicy::Expanding);
  editDescriptionLabel->setAlignment(Qt::AlignTop);
  descriptionScrollArea->setWidget(editDescriptionLabel);
  descriptionScrollArea->setWidgetResizable(true);
  descriptionScrollArea->setAlignment(Qt::AlignTop);
  descriptionScrollArea->setSizePolicy(QSizePolicy::Preferred,
                                       QSizePolicy::Expanding);
  editFormLayout->addRow("Name: ", editNameLabel);
  editFormLayout->addRow("Quantity: ", editQuantityBox);
  editFormLayout->addRow("Tags:", editTagsLabel);

  editBox->addLayout(editFormLayout);
  editBox->addSpacing(20);
  editBox->addWidget(new QLabel{"Description:"});
  editBox->addWidget(descriptionScrollArea);
  layout->addWidget(editFields);
}

void ItemInfoWindow::initEditButton() {
  editButton->setFlat(true);
  editButton->setCheckable(true);
  editButton->setIcon(QIcon(":/icons/edit-pencil.svg"));
  connect(editButton, &QPushButton::clicked, this,
          [this]() { toggleEditing(); });
}

void ItemInfoWindow::toggleEditing() {
  // TODO: Implement?
  qDebug() << "Toggled editing";
  editing = !editing;
  editFields->setVisible(editing);
  viewFields->setVisible(!editing);
}

void ItemInfoWindow::updateItem(Item *selectedItem) {
  this->item = selectedItem;
  if (item) {
    title->setText(QString("<b>%1</b>").arg(item->name));
    
    QString name{item->name};
    viewNameLabel->setText(name);
    editNameLabel->setText(name);
    
    unsigned int quantity = item->quantity;
    viewQuantityLabel->setText(QString::number(quantity));
    editQuantityBox->setValue(quantity);
    
    QString tags{QStringList::fromVector(item->tags).join(", ")};
    viewTagsLabel->setText(tags);
    editTagsLabel->setText(tags);
    
    QString description = item->description;
    viewDescriptionLabel->setText(description);
    editDescriptionLabel->setText(description);

    viewFields->setVisible(!editing);
    editFields->setVisible(editing);
    tip->setVisible(false);
    editButton->setVisible(true);
    
    return;
  }
  title->setText("<b>Item info</b>");
  title->setAlignment(Qt::AlignVCenter);
  
  for (auto label : {viewNameLabel, viewQuantityLabel, viewTagsLabel, viewDescriptionLabel}) {
    label->setText("null");
  }
  for (auto lineEdit: {editNameLabel, editTagsLabel}) {
    lineEdit->setText("null");
  }
  editDescriptionLabel->setText("null");
  editQuantityBox->setValue(0);
  
  viewNameLabel->setText("null");
  viewQuantityLabel->setText("null");
  viewTagsLabel->setText("null");
  viewDescriptionLabel->setText("null");
  viewFields->setVisible(false);
  editFields->setVisible(false);
  tip->setVisible(true);
  editButton->setVisible(false);
}
