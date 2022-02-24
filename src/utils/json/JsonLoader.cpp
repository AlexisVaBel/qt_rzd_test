#include "JsonLoader.h"
#include <QFile>
#include <QJsonDocument>

#include <QDebug>

using namespace utils::json;

JsonLoader::JsonLoader(QString filePath)
	: _path(std::move(filePath)) {
	QFile _loadFile;
}

JsonLoader::~JsonLoader() {
	_loadFile.close();
}

bool JsonLoader::isFileValid() {
	_loadFile.setFileName(_path);
	if (!_loadFile.open(QIODevice::ReadOnly)) {
		qDebug() << _loadFile.fileName();
		return false;
	}
	return true;
}

QJsonDocument JsonLoader::load() {
	QByteArray loadedData = _loadFile.readAll();

	QJsonDocument loadDoc(QJsonDocument::fromJson(loadedData));

	return std::move(loadDoc);
}
