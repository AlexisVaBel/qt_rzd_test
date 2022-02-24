//
// Created by abel on 24.02.2022.
//
#pragma once
#include <QFile>
#include <QString>

class QJsonDocument;

namespace utils::json {

class JsonLoader {
public:
	JsonLoader(QString filePath);
	~JsonLoader();

	bool isFileValid();
	QJsonDocument load();

private:
	QString _path;
	QFile _loadFile;
};

} // namespace utils::json