// Copyright [2025] Auli Jussila & Mikko Memonen

#include "../include/o4_project/main_window.h"
#include <QApplication>

int main(int argc, char *argv[]) {
  // Testing testing...
  QApplication app(argc, argv);
  MainWindow mainWindow;
  mainWindow.show();

  return app.exec();
}
