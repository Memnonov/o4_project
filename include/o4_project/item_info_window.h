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
#include "item.h"

class ItemInfoWindow : public QFrame {
  Q_OBJECT;

 public:
  explicit ItemInfoWindow(QWidget *parent = nullptr);
  ~ItemInfoWindow() = default;

 private:
  QString itemName = "Dummy Item";
  unsigned int itemQuantity = 666;
  QVector<QString> itemTags = {"cool", "beans", "my man"};
  QString itemDescription = {R"(
    This here is my item. Consider it superior to your item.
    Coolness +666, Rad +420, Other stuff + a lot too!
  )"};
  
  // TODO: Clean this up when actually connecting to the data model?
  bool editing = false;
  Item *item = nullptr;
  QLabel *tip;
  QWidget *topPanel;
  QVBoxLayout *layout;
  QWidget *viewFields;
  QWidget *editFields;
  QLabel *title;
  QPushButton *editButton;
  QLabel *viewNameLabel;
  QLineEdit *editNameLabel;
  QLabel *viewQuantityLabel;
  QSpinBox *editQuantityBox;
  QLabel *viewTagsLabel;
  QLineEdit *editTagsLabel;
  QLabel *viewDescriptionLabel;
  QTextEdit *editDescriptionLabel;

  void initViewFields();
  void initEditFields();
  void initEditButton();
  void toggleEditing();

 public slots:
  void updateItem(Item *item = nullptr);

 signals:
};

#endif // !ITEM_INFO_WINDOW_H
