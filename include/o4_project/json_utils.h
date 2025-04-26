// Copyright [2025] Auli Jussila & Mikko Memonen

#ifndef JSON_UTILS_H
#define JSON_UTILS_H

#include <QByteArray>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QString>
#include <QStringList>
#include <QVector>
#include <QtLogging>
#include "container.h"
#include "item.h"
#include <memory>
#include <qlogging.h>

namespace JSONUtils {
QVector<std::shared_ptr<Container>> parseInventoryFromFile(QString path);
QVector<std::shared_ptr<Container>> parseInventoryFromJSON(QJsonDocument json);
QStringList getTags(QJsonArray tags);

inline QVector<std::shared_ptr<Container>>
parseInventoryFromFile(QString path) {
  QFile file{path};
  if (!file.open(QIODeviceBase::ReadOnly)) {
    qDebug() << "Couldn't open data file.";
    return {};
  }

  QByteArray bytes = file.readAll();
  if (bytes.isEmpty()) {
    qDebug() << "Data JSON was empty";
    return {};
  }

  auto json = QJsonDocument::fromJson(bytes);
  if (json.isNull()) {
    qDebug() << "Couldn't read JSON from data.";
    return {};
  }

  return parseInventoryFromJSON(json);
}

inline QVector<std::shared_ptr<Container>>
parseInventoryFromJSON(QJsonDocument json) {
  auto obj = json.object();
  if (obj.isEmpty() ||
      !obj.contains("containers") || !obj["containers"].isArray()) {
    qDebug() << "Invalid data JSON";
    return {};
  }

  auto containers = obj["containers"].toArray();
  QVector<std::shared_ptr<Container>> resultContainers;
  for (const QJsonValue &value : containers) {
    if (!value.isObject()) {
      qDebug() << "Invalid data JSON";
      continue;
    }
    auto containerObj = value.toObject();
    auto container =
        std::make_shared<Container>(containerObj["name"].toString());
    qDebug() << "\nCreated container " + container->name;

    auto items = containerObj["items"].toArray();
    for (const QJsonValue &value : items) {
      auto itemObj = value.toObject();
      auto item = std::make_shared<Item>(
          itemObj["name"].toString(), itemObj["quantity"].toInt(),
          itemObj["description"].toString(), getTags(itemObj["tags"].toArray()),
          itemObj["favourite"].toBool());
      container->addItem(item);
    }
    resultContainers.push_back(container);
  }
  return resultContainers;
}

inline QStringList getTags(QJsonArray tags) {
  QStringList result;
  for (const QJsonValue &value : tags) {
    result.push_back(value.toString());
  }
  return result;
}

} // namespace JSONUtils

#endif // !JSON_UTILS_H
