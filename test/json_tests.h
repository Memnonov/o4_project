// Copyright [2025] Auli Jussila & Mikko Memonen

#ifndef JSON_TESTS_H
#define JSON_TESTS_H

#include "../include/o4_project/json_utils.h"
#include <QByteArray>
#include <QJsonDocument>
#include <QTest>
#include <QtLogging>
#include <qlogging.h>
#include <qtestcase.h>
#include <qtmetamacros.h>

class JsonTests : public QObject {
  Q_OBJECT;

private slots:
  void testParseJsonDocument();
};

inline void JsonTests::testParseJsonDocument() {
  QJsonDocument json;
  auto string = R"(
  {
    "containers": [
      {
        "name": "container",
        "items": [
          {
            "name": "name",
            "quantity": 1,
            "description": "test",
            "tags": [
              "tag"
            ],
            "favourite": false
          }
]
      }
    ]
  } 
  )";


  QByteArray bytes{string};
  auto document = QJsonDocument::fromJson(bytes);
  auto result = JSONUtils::parseInventoryFromJSON(document);
  QVERIFY(result.length() == 1);
  auto container = result.at(0);
  QVERIFY(container);
  QCOMPARE(container->name, "container");
  auto item = container->removeItem(0);
  QCOMPARE(item->name, "name");
  QCOMPARE(item->quantity, 1);
  QCOMPARE(item->tags.at(0), "tag");
  QCOMPARE(item->favourite, false);
}

#endif // !JSON_TESTS_H
