
#include "RoutesAgregate.h"

#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>

using namespace client::entity;

void RoutesAgregate::read(const QJsonObject& json) {
	QStringList const keys = json.keys();

	for (const QString key : keys) {
		QJsonArray innerArray = json[key].toArray();
		if (key == "categories") {
			_readCategories(innerArray);
		}
		if (key == "full") {
			_readFull(innerArray);
		}
		if (key == "summary") {
			_readSummary(innerArray);
		}
	}
}

//std::unordered_map<int, QString> _category;
void RoutesAgregate::_readFull(const QJsonArray& json) {
	_routesFull.reserve(json.size());
	for (int index = 0; index < json.size(); ++index) {
		_routesFull.emplace_back(Route());
		_routesFull.rbegin()->read(json[index].toObject());
	}
}

void RoutesAgregate::_readCategories(const QJsonArray& json) {
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
			id = currentObject["category_id"].toInt();
		} else {
			continue;
		}
		_category.insert({name, id});
	}
}

void RoutesAgregate::_readSummary(const QJsonArray& json) {
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

std::vector<Route> RoutesAgregate::getRoutes() {
	return _routesFull;
}

std::vector<Route> RoutesAgregate::getSummary() {
	return _routesSummary;
}

int RoutesAgregate::getIdByCategory(QString category) {
	return _category.at(category);
}
