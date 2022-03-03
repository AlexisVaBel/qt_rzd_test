#pragma once

#include <QJsonObject>
#include <QString>
#include <vector>

namespace client::entity {
class Route;
class IConfigProducer {
public:
	virtual ~IConfigProducer() {
	}
	virtual void read(const QJsonObject& json) = 0;

	virtual std::vector<QString> getCategories() = 0;
	virtual std::vector<Route> getRoutes() = 0;
	virtual std::vector<Route> getSummary() = 0;

	virtual int getIdByCategory(QString category) = 0;
};
} // namespace client::entity
