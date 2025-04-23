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
#include "../o4_project/navigation_panel.h"
#include "../o4_project/container_window.h"
#include "../o4_project/items_window.h"
#include "../o4_project/item_info_window.h"
#include "../o4_project/search_window.h"
#include "../o4_project/move_window.h"
#include "browse_window.h"
#include "items_window.h"
#include "search_window.h"
#include "tutorial_window.h"
#include "about_window.h"

class MainWindow : public QMainWindow {
  Q_OBJECT;

 public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow() = default;

 private:
  QStackedWidget *mainStack;
  BrowseWindow *browseWindow;
  SearchWindow *searchWindow;
  MoveWindow *moveWindow;
  TutorialWindow *tutorialWindow;
  AboutWindow *aboutWindow;
  
  NavigationPanel *navigationPanel;
  ContainerWindow *containerWindow;
  ItemsWindow *itemsWindow;
  ItemInfoWindow *infoWindow;
  
  QStackedWidget *leftStack;
  QStackedWidget *rightStack;
  
  QFrame* leftWindowFrame;
  QFrame* rightWindowFrame;

  void initMainStack();

 private slots:
  void handleNavigation(NavigationPanel::NavAction action);
};

#endif  // !MAIN_WINDOW_H
