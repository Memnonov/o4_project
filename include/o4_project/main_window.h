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
#include "navigation_panel.h"
#include "container_window.h"
#include "items_window.h"
#include "item_info_window.h"
#include "search_model.h"
#include "search_window.h"
#include "move_window.h"
#include "browse_window.h"
#include "items_window.h"
#include "search_window.h"
#include "status_bar.h"
#include "tutorial_window.h"
#include "about_window.h"
#include "container_model.h"

class MainWindow : public QMainWindow {
  Q_OBJECT;

 public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow() = default;

 private:
  ContainerModel *model;
  SearchModel *searchModel;
  QWidget *mainArea;
  QStackedWidget *mainStack;
  BrowseWindow *browseWindow;
  SearchWindow *searchWindow;
  MoveWindow *moveWindow;
  TutorialWindow *tutorialWindow;
  AboutWindow *aboutWindow;
  StatusBar *statusBar;
  
  NavigationPanel *navigationPanel;
  ContainerWindow *containerWindow;
  ItemsWindow *itemsWindow;
  ItemInfoWindow *infoWindow;
  
  QStackedWidget *leftStack;
  QStackedWidget *rightStack;
  
  QFrame* leftWindowFrame;
  QFrame* rightWindowFrame;

  void initMainArea();

 private slots:
  void handleNavigation(NavigationPanel::NavAction action);
  void initConnections();
};

#endif  // !MAIN_WINDOW_H
