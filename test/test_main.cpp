// Copyright [2025] Auli Jussila & Mikko Memonen

#include "./container_tests.h"
#include "container_model_tests.h"
#include <QCoreApplication>
#include <QTest>
#include <qcoreapplication.h>
#include <qlogging.h>
#include <qtestcase.h>
#include "./json_tests.h"

int main(int argc, char** argv) {
  QCoreApplication app(argc, argv);

  int status = 0;

  ContainerTests containerTests;
  status |= QTest::qExec(&containerTests, argc, argv);
  qDebug() << "";

  ContainerModelTests modelTests;
  status |= QTest::qExec(&modelTests, argc, argv);
  qDebug() << "";

  JsonTests jsonTests;
  status |= QTest::qExec(&jsonTests, argc, argv);
  qDebug() << "";

  return status;
}
