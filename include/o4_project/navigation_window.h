// Copyright [2025] Auli Jussila & Mikko Memonen

#ifndef NAVIGATION_WINDOW_H
#define NAVIGATION_WINDOW_H

#include <QHBoxLayout>
#include <QLabel>
#include <QObject>
#include <QPushButton>
#include <QString>
#include <QWidget>
#include <qcontainerfwd.h>
#include <QMap>
#include <qmap.h>
#include <qpushbutton.h>

class NavigationWindow : public QWidget {
  Q_OBJECT;

 public:
  enum class NavAction {
    BrowseItems,
    SearchItems,
    MoveItems,
    Tutorial,
    About,
    Quit
  };

  static const QMap<NavAction, QString> navActionMap;

  static QString navActionToString(NavAction action);

  explicit NavigationWindow(QWidget *parent = nullptr);
  ~NavigationWindow() = default;


 private:
  QVBoxLayout *layout;
  QVector<QString> buttons = {"APP LOGO",     "stretch",    "Browse items",
                              "Search items", "Move items", "stretch",
                              "Tutorial",     "About",      "Quit"};
  void addButton(NavAction action);

 signals:
  void buttonPressed(NavAction action);
};

#endif  // !NAVIGATION_WINDOW_H
