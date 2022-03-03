#pragma once

#include <QString>

#include "IConfigProducer.h"
#include "Route.h"

#include <map>
#include <QJsonArray>
#include <vector>

class QJsonObject;

namespace client::entity {

class RoutesAgregate : public IConfigProducer {
public:
	void read(const QJsonObject& json) override;

	std::vector<QString> getCategories() override;
	std::vector<Route> getRoutes() override;
	std::vector<Route> getSummary() override;
	int getIdByCategory(QString category) override;

private:
	void _readFull(const QJsonArray& json);
	void _readCategories(const QJsonArray& json);
	void _readSummary(const QJsonArray& json);

	std::vector<Route> _routesFull;
	std::vector<Route> _routesSummary;
	std::map<QString, int> _category;
};

} // namespace client::entity
