// Copyright [2025] Auli Jussila & Mikko Memonen

#ifndef NAVIGATION_WINDOW_H
#define NAVIGATION_WINDOW_H

#include <QObject>
#include <QString>
#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>
#include <qcontainerfwd.h>
#include <qpushbutton.h>

class NavigationWindow : public QWidget {
  Q_OBJECT;

 public:
  explicit NavigationWindow(QWidget *parent = nullptr);
  ~NavigationWindow() = default;

 private:
  QVBoxLayout *layout;
  QVector<QString> buttons = {"Browse", "Move", "Search", "Quit"};
  void addButton(const QString& label);
};

#endif  // !NAVIGATION_WINDOW_H
