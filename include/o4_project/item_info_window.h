// Copyright [2025] Auli Jussila & Mikko Memonen

#ifndef ITEM_INFO_WINDOW_H
#define ITEM_INFO_WINDOW_H

#include <QFormLayout>
#include <QFrame>
#include <QObject>
#include <QPushButton>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QLabel>
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
  Item dummyItem{"Dummy item", 666, "Item description", {"tag", "tag", "tag"}};

  Item *item = nullptr;
  QVBoxLayout *layout;
  QWidget *viewFields;
  QWidget *editFields;
  QLabel *title;
  QPushButton *editButton;
  QLabel *viewNameLabel;
  QLabel *viewQuantityLabel;
  QLabel *viewTagsLabel;
  QLabel *viewDescriptionLabel;

  void initViewFields();

 public slots:
  void updateItem(Item *item);

 signals:
};

#endif // !ITEM_INFO_WINDOW_H
