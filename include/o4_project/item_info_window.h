// Copyright [2025] Auli Jussila & Mikko Memonen

#ifndef ITEM_INFO_WINDOW_H
#define ITEM_INFO_WINDOW_H

#include <QStackedWidget>
#include <QToolBar>
#include <QFormLayout>
#include <QFrame>
#include <QObject>
#include <QPushButton>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QLabel>
#include <QTextEdit>
#include <QLineEdit>
#include <QSpinBox>
#include <QString>
#include <qlogging.h>
#include "item.h"
#include "container.h"

class ItemInfoWindow : public QFrame {
  Q_OBJECT;

 public:
  explicit ItemInfoWindow(QWidget *parent = nullptr);
  ~ItemInfoWindow() = default;
  void setEditable(bool editable) {
    this->editable = editable;
  }
  void setFavouritable(bool favouritable) {
    favouriteButton->setEnabled(favouritable);
  }

 private:
  // State
  bool editing = false;
  bool editable = true;
  Item *item = nullptr;
  Container *container = nullptr;
  
  QLabel *title;
  QLabel *tip;
  QWidget *topPanel;
  QVBoxLayout *layout;
  QPushButton *editButton;
  QPushButton *favouriteButton;
  
  // View mode.
  QWidget *viewFields;
  QLabel *viewNameLabel;
  QLabel *viewQuantityLabel;
  QLabel *viewTagsLabel;
  QLabel *viewDescriptionLabel;
  
  // Edit mode
  QWidget *editFields;
  QLineEdit *editNameLabel;
  QSpinBox *editQuantityBox;
  QLineEdit *editTagsLabel;
  QTextEdit *editDescriptionLabel;
  
  void initViewFields();
  void initEditFields();
  void initEditButton();
  void initFavouriteButton();
  void refresh();
  void toggleEditing();
  void showViews();
  void hideViews();
  void setFieldsNull();
  void updateFavouriteButton();
  QScrollArea* makeDescriptionScrollArea();

 public slots:
  void handleItemSelected(Item *item = nullptr, Container *container = nullptr);
  void handleFavouriteButtonClicked();
};

#endif // !ITEM_INFO_WINDOW_H
