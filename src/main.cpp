// Copyright [2025] Auli Jussila & Mikko Memonen

#include "../include/o4_project/main_window.h"
#include "../include/o4_project/json_utils.h"
#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  MainWindow mainWindow;
  mainWindow.show();

  return app.exec();
}
