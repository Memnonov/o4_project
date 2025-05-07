// Copyright [2025] Auli Jussila & Mikko Memonen

#include "../include/o4_project/item_info_window.h"
#include <QLineEdit>
#include <QSpinBox>
#include <QStringList>
#include <QTextEdit>
#include <qpushbutton.h>

ItemInfoWindow::ItemInfoWindow(QWidget *parent)
    : QFrame(parent), title{new QLabel}, layout{new QVBoxLayout{this}},
      tip{new QLabel{}}, topPanel{new QWidget}, editButton{new QPushButton},
      favouriteButton{new QPushButton}, viewFields{new QWidget},
      goToItemButton{new QPushButton}, viewNameLabel{new QLabel},
      viewQuantityLabel{new QLabel}, viewTagsLabel{new QLabel},
      viewDescriptionLabel{new QLabel}, editFields{new QWidget},
      editNameLabel{new QLineEdit}, editQuantityBox{new QSpinBox},
      editTagsLabel{new QLineEdit}, editDescriptionLabel(new QTextEdit) {
  layout->setAlignment(Qt::AlignTop);
  setFrameShape(StyledPanel);

  initFavouriteButton();
  initEditButton();
  initGoToItemButton();

  tip->setAlignment(Qt::AlignCenter);
  tip->setText("Select a container from the left to browse items.");
  tip->setWordWrap(true);

  auto topPanelLayout = new QHBoxLayout{topPanel};
  topPanelLayout->addWidget(favouriteButton);
  title->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  topPanelLayout->addWidget(title);
  topPanelLayout->addWidget(editButton, 0, Qt::AlignTop);
  topPanelLayout->addWidget(goToItemButton, 0, Qt::AlignTop);

  layout->addWidget(topPanel);
  tip->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  layout->addWidget(tip);

  initViewFields();
  initEditFields();
  handleItemSelected();
}

void ItemInfoWindow::initViewFields() {
  auto viewBox = new QVBoxLayout{viewFields};
  auto viewFormLayout = new QFormLayout;
  auto descriptionScrollArea = makeDescriptionScrollArea();

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
  auto editBox = new QVBoxLayout{editFields};
  auto editFormLayout = new QFormLayout;
  auto descriptionScrollArea = makeDescriptionScrollArea();

  editNameLabel->setPlaceholderText("Item name");
  editNameLabel->setText(item ? item->name : "");

  editQuantityBox->setMaximum(9999);
  editQuantityBox->setValue(item ? item->quantity : 0);

  editTagsLabel->setPlaceholderText("Separate tags with #: #tag1 #tag2 #tag3");

  editDescriptionLabel->setPlaceholderText("Write item description here.");
  editDescriptionLabel->setLineWrapMode(QTextEdit::WidgetWidth);
  editDescriptionLabel->setSizePolicy(QSizePolicy::Preferred,
                                      QSizePolicy::Expanding);
  editDescriptionLabel->setAlignment(Qt::AlignTop);
  descriptionScrollArea->setWidget(editDescriptionLabel);
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

void ItemInfoWindow::initGoToItemButton() {
  goToItemButton->setIcon(QIcon{":/icons/doc-magnifying-glass.svg"});
  goToItemButton->setFlat(true);
  goToItemButton->setVisible(false);
  goToItemButton->setText("Go to Item");
  connect(goToItemButton, &QPushButton::clicked, this, [this]() {
    if (item && container) {
      emit goToItemClicked(item, container);
    }
  });
}

void ItemInfoWindow::toggleEditing() {
  qDebug() << "Toggled editing";
  editing = !editing;
  editFields->setVisible(editing);
  viewFields->setVisible(!editing);
}

void ItemInfoWindow::handleItemSelected(Item *selectedItem,
                                        Container *container) {
  this->item = selectedItem;
  this->container = container;

  if (!item || !container) {
    title->setText("<b>Item info</b>");
    title->setAlignment(Qt::AlignVCenter);
    hideViews();
    return;
  }
  refresh();
  showViews();
}

// TODO: Combine this and the one below? : D
void ItemInfoWindow::showViews() {
  viewFields->setVisible(!editing);
  editFields->setVisible(editing);
  tip->setVisible(false);
  editButton->setVisible(true && editable);
  favouriteButton->setVisible(true);
  goToItemButton->setVisible(canGoTo);
}

void ItemInfoWindow::hideViews() {
  viewFields->setVisible(false);
  editFields->setVisible(false);
  tip->setVisible(true);
  editButton->setVisible(false);
  favouriteButton->setVisible(false);
  goToItemButton->setVisible(false);
}

// This is mostly for debugging use.
// You shouldn't see nulls in the app anymore.
void ItemInfoWindow::setFieldsNull() {
  for (auto label : {viewNameLabel, viewQuantityLabel, viewTagsLabel,
                     viewDescriptionLabel}) {
    label->setText("null");
  }
  for (auto lineEdit : {editNameLabel, editTagsLabel}) {
    lineEdit->setText("null");
  }
  editQuantityBox->setValue(0);
  editDescriptionLabel->setText("null");
}

QScrollArea *ItemInfoWindow::makeDescriptionScrollArea() {
  auto scrollArea = new QScrollArea;
  scrollArea->setWidgetResizable(true);
  scrollArea->setAlignment(Qt::AlignTop);
  scrollArea->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
  return scrollArea;
}

void ItemInfoWindow::refresh() {
  if (!item) {
    return;
  }
  title->setText(
      QString("<b>%1</b><br><i>%2</i>").arg(item->name).arg(container->name));

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
  updateFavouriteButton();
}

void ItemInfoWindow::initFavouriteButton() {
  favouriteButton->setIcon(QIcon{":/icons/star.svg"});
  favouriteButton->setFlat(true);
  connect(favouriteButton, &QPushButton::clicked, this,
          &ItemInfoWindow::handleFavouriteButtonClicked);
}

void ItemInfoWindow::updateFavouriteButton() {
  auto icon =
      QString(":/icons/%1.svg").arg(item->favourite ? "star-solid" : "star");
  favouriteButton->setIcon(QIcon{icon});
}

void ItemInfoWindow::handleFavouriteButtonClicked() {
  qDebug() << "Clicked favourite button.";
  emit favouriteButtonClicked(item, container);
  updateFavouriteButton();
}
