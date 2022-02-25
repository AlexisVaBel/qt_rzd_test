
#include "RoutesAgregate.h"

#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>

#include "Route.h"

using namespace client::entity;

void RoutesAgregate::read(const QJsonObject& json) {
	QStringList const keys = json.keys();

	for (const QString key : keys) {
		QJsonArray innerArray = json[key].toArray();
		if (key == "categories") {
			readCategories(innerArray);
		}
		if (key == "full") {
			readFull(innerArray);
		}
		if (key == "summary") {
			readSummary(innerArray);
		}
	}
}

//std::unordered_map<int, QString> _category;
void RoutesAgregate::readFull(const QJsonArray& json) {
	_routesFull.reserve(json.size());
	for (int index = 0; index < json.size(); ++index) {
		_routesFull.emplace_back(Route());
		_routesFull.rbegin()->read(json[index].toObject());
	}
}

void RoutesAgregate::readCategories(const QJsonArray& json) {
	int id{0};
	QString name{""};
	for (int index = 0; index < json.size(); ++index) {
		QJsonObject currentObject = json[index].toObject();
		if (currentObject.contains("name") && currentObject["name"].isString()) {
			name = currentObject["name"].toString();
		} else {
			continue;
		}
		if (currentObject.contains("category_id") && currentObject["category_id"].isDouble()) {
			id = currentObject["id"].toInt();
		} else {
			continue;
		}
		_category.insert({name, id});
	}
}

void RoutesAgregate::readSummary(const QJsonArray& json) {
	_routesSummary.reserve(json.size());
	for (int index = 0; index < json.size(); ++index) {
		_routesSummary.emplace_back(Route());
		_routesSummary.rbegin()->read(json[index].toObject());
	}
}
std::vector<QString> RoutesAgregate::getCategories() {
	std::vector<QString> categoryList;
	for (auto const [key, _] : _category) {
		categoryList.push_back(key);
	}
	return categoryList;
}
