#include "Route.h"
#include <QJsonArray>
#include <QJsonObject>

using namespace client::entity;

Route::Route(int id, QString shortName)
	: _id(id)
	, _shortName(std::move(shortName)) {
}

Route::Route() {
}

void Route::appendCategory(int id) {
	_categories.push_back(id);
}

void Route::setImage(QString stringUrl) {
	_imageSource = std::move(stringUrl);
}

void Route::appendImageSource(QString stringUrl) {
	_imageSourceList.push_back(std::move(stringUrl));
}

void Route::read(const QJsonObject& json) {
	if (json.contains("object_id") && json["object_id"].isDouble()) {
		_id = json["object_id"].toInt();
	}
	if (json.contains("short_name") && json["short_name"].isString()) {
		_shortName = json["short_name"].toString();
	}
	if (json.contains("title") && json["title"].isString()) {
		_title = json["title"].toString();
	}
	if (json.contains("content") && json["content"].isString()) {
		_content = json["content"].toString();
	}
	if (json.contains("image") && json["image"].isString()) {
		_imageSource = json["image"].toString();
	}
	if (json.contains("categories") && json["categories"].isArray()) {
		QJsonArray categories = json["categories"].toArray();
		_categories.reserve(categories.size());
		for (int index = 0; index < categories.size(); ++index) {
			_categories.push_back(categories[index].toInt(0));
		}
	}
	if (json.contains("images") && json["images"].isArray()) {
		QJsonArray images = json["images"].toArray();
		_imageSourceList.reserve(images.size());
		for (int index = 0; index < images.size(); ++index) {
			_imageSourceList.push_back(images[index].toString(""));
		}
	}
}
