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
class ItemInfoWindow : public QFrame {
  Q_OBJECT;

 public:
  explicit ItemInfoWindow(QWidget *parent = nullptr);
  ~ItemInfoWindow() = default;

 private:
  QString itemName = "Dummy Item";
  unsigned int itemQuantity = 666;
  QVector<QString> itemTags = {"cool", "beans"};
  QString itemDescription = {"This here is my item. Consider it superior to your item."};
  
  QVBoxLayout *layout;
  QWidget *viewFields;
  QWidget *editFields;
  QLabel *title;
  QPushButton *editButton;

 signals:
};

#endif // !ITEM_INFO_WINDOW_H
