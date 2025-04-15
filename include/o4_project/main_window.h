// Copyright [2025] Auli Jussila & Mikko Memonen

#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QLabel>
#include <qwidget.h>
#include "../o4_project/navigation_window.h"
#include "../o4_project/container_window.h"

class MainWindow : public QMainWindow {
  Q_OBJECT;

 public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow() = default;

 private:
  NavigationWindow *navigationWindow;
  ContainerWindow *containerWindow;

 private slots:
  void handleNavigation(NavigationWindow::NavAction action);
};

#endif  // !MAIN_WINDOW_H
