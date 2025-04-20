// Copyright [2025] Auli Jussila & Mikko Memonen

#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QLabel>
#include <qframe.h>
#include <qstackedwidget.h>
#include <qwidget.h>
#include "../o4_project/navigation_window.h"
#include "../o4_project/container_window.h"
#include "../o4_project/items_window.h"
#include "../o4_project/item_info_window.h"
#include "items_window.h"

class MainWindow : public QMainWindow {
  Q_OBJECT;

 public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow() = default;

 private:
  NavigationWindow *navigationWindow;
  ContainerWindow *containerWindow;
  ItemsWindow *itemsWindow;
  ItemInfoWindow *infoWindow;
  QStackedWidget *leftStack;
  QStackedWidget *rightStack;
  QFrame* leftWindowFrame;
  QFrame* rightWindowFrame;

 private slots:
  void handleNavigation(NavigationWindow::NavAction action);
  void handleContainerClicked();
  void handleBackButton();
};

#endif  // !MAIN_WINDOW_H
