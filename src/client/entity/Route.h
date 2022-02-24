//
// Created by abel on 23.02.2022.
//

#pragma once

#include <QString>
#include <QStringList>
#include <vector>

class QJsonObject;
namespace client::entity {

class Route {
public:
	Route(int id, QString shortName);
	Route();
	void appendCategory(int id);
	void setImage(QString stringUrl);
	void appendImageSource(QString stringUrl);

	void read(const QJsonObject& json);
	//void write(const QJsonObject &json);

private:
	int _id{0};
	QString _shortName{""};
	QString _title{""};
	QString _content{""};
	std::vector<int> _categories;
	QString _imageSource{""}; // not clear why in json is used image and images?
	QStringList _imageSourceList;
};

} // namespace client::entity
