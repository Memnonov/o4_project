// Copyright [2025] Auli Jussila & Mikko Memonen

#include "./container_tests.h"
#include <QCoreApplication>
#include <QTest>
#include <qcoreapplication.h>
#include <qtestcase.h>

int main(int argc, char** argv) {
  QCoreApplication app(argc, argv);

  int status = 0;

  ContainerTests containerTests;
  status |= QTest::qExec(&containerTests, argc, argv);

  return status;
}
