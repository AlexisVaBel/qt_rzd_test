//
// Created by abel on 24.02.2022.
//

#pragma once
#include <vector>

class QJsonObject;

namespace client::entity {

class Route;

class RoutesAgregate {
public:
	void read(const QJsonObject& json);

private:
	void readRoutes(const QJsonObject& json);
	void readCategories(const QJsonObject& json);
	void readSummary(const QJsonObject& json);

	std::vector<Route> _routes;
};

} // namespace client::entity
