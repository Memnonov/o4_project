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
#include <container.h>
#include <item.h>
#include <memory>
#include <qcontainerfwd.h>
#include <qiodevicebase.h>
#include <qjsonvalue.h>
#include <qlogging.h>

namespace JSONUtils {
QVector<std::shared_ptr<Container>> initInventoryFromJSON(QString path);
inline QVector<std::shared_ptr<Container>> initInventoryFromJSON(QString path) {
  QVector<std::shared_ptr<Container>> resultContainers;
  QFile file{path};
  if (!file.open(QIODeviceBase::ReadOnly)) {
    qDebug() << "Couldn't open data file.";
    return resultContainers;
  }

  QByteArray bytes = file.readAll();
  if (bytes.isEmpty()) {
    qDebug() << "Data JSON was empty";
    return resultContainers;
  }

  auto json = QJsonDocument::fromJson(bytes);
  if (json.isNull()) {
    qDebug() << "Couldn't read JSON from data.";
    return resultContainers;
  }

  auto obj = json.object();
  if (obj.isEmpty() || !obj.contains("containers") ||
      !obj["containers"].isArray()) {
    qDebug() << "Invalid data JSON";
  }

  auto containers = obj["containers"].toArray();
  for (const QJsonValue &value : containers) {
    if (!value.isObject()) {
      qDebug() << "Invalid data JSON";
      continue;
    }
    auto containerObj = value.toObject();
    auto container =
        std::make_shared<Container>(containerObj["name"].toString());
    qDebug() << "Created container " + container->name;

    auto items = containerObj["items"].toArray();
    for (const QJsonValue &value : items) {
      auto itemObj = value.toObject();
      auto item = std::make_shared<Item>(
          itemObj["name"].toString(), itemObj["quantity"].toInt(),
          itemObj["description"].toString(),
          QStringList{"Implement tags, you lazy son of a gun!"});
      container->addItem(item);
      qDebug() << "  Added item: " + item->name;
    }
  }

  return resultContainers;
}

#endif // !JSON_UTILS_H
}
