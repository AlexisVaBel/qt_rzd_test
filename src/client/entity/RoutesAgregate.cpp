//
// Created by abel on 24.02.2022.
//

#include "RoutesAgregate.h"

#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>

using namespace client::entity;

void RoutesAgregate::read(const QJsonObject& json) {
	QStringList const keys = json.keys();

	for (const QString key : keys) {
		qDebug() << "key is " << key;
		if (key == "full") {
//			readRoutes(*json.find(key));
		}
	}
}

void RoutesAgregate::readRoutes(const QJsonObject& json) {
}
void RoutesAgregate::readCategories(const QJsonObject& json) {
}
void RoutesAgregate::readSummary(const QJsonObject& json) {
}
