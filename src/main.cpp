// Copyright [2025] Auli Jussila & Mikko Memonen

#include <cstdlib>
#include <QApplication>
#include <QMainWindow>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  QMainWindow mainWindow;
  mainWindow.setWindowTitle("o4_project");
  mainWindow.resize(666, 666);

  mainWindow.show();

  return app.exec();
}
