// Copyright [2025] Auli Jussila & Mikko Memonen

#include "../include/o4_project/item.h"
#include <QApplication>
#include <QMainWindow>
#include <cstdlib>
#include <QtLogging>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  QMainWindow mainWindow;
  mainWindow.setWindowTitle("o4_project");
  mainWindow.resize(666, 666);

  Item testItem{
      "Tavara", 666, "Tällästä tavarantynkää tällä kertaa.", {"tagi", "tägi"}};

  qInfo() << testItem.name << " | " << testItem.quantity << " | "
          << testItem.description << "\n";

  mainWindow.show();

  return app.exec();
}
