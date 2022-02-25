#pragma once

#include <QString>

#include <map>
#include <QJsonArray>
#include <vector>

class QJsonObject;

namespace client::entity {

class Route;

class RoutesAgregate {
public:
	void read(const QJsonObject& json);

	std::vector<QString> getCategories();

private:
	void readFull(const QJsonArray& json);
	void readCategories(const QJsonArray& json);
	void readSummary(const QJsonArray& json);

	std::vector<Route> _routesFull;
	std::vector<Route> _routesSummary;
	std::map<QString, int> _category;
};

} // namespace client::entity
