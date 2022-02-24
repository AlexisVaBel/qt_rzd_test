#include "MainWindow.h"
#include "DetailsFrame.h"
#include "SearchFrame.h"

#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>

#include <entity/Route.h>
#include <entity/RoutesAgregate.h>

#include <utils/json/JsonLoader.h>

using namespace ui::application;

MainWindow::MainWindow(QWidget* parent, QString pathConfig)
	: Super(parent)
	, _jsonLoader(std::make_unique<utils::json::JsonLoader>(pathConfig))
	, _controller(std::make_unique<ui::controller::NetworkImageController>())
	, _widgetContainer(new QStackedWidget(this)) {
	QFile styleFile(":/app.qss");
	styleFile.open(QFile::OpenModeFlag::ReadOnly);
	QString const styleSheet(styleFile.readAll());
	setStyleSheet(styleSheet);

	// tests for loading
	_controller->addUrl("https://www.rzd.ru/api/media/resources/1787985");
	_controller->addUrl("https://www.rzd.ru/api/media/resources/1797111");
	_controller->addUrl("https://www.rzd.ru/api/media/resources/1761235");
	_controller->addUrl("https://www.rzd.ru/api/media/resources/1784814");
	_controller->addUrl("https://www.rzd.ru/api/media/resourcess/1707466");
	_controller->addUrl("https://www.rzd.ru/api/media/resources/1787985");
	_controller->addUrl("https://www.rzd.ru/api/media/resources/1707466");

	//

	client::entity::RoutesAgregate routesAgregate;

	if (_jsonLoader->isFileValid()) {
		QJsonDocument document = _jsonLoader->load();
		routesAgregate.read(document.object());
	} else {
		qDebug() << ("file is not readable... ");
	}
	constructFrames();
}

void MainWindow::constructFrames() {
	//not setting parent to hide possible artefacts
	_pageCategories = new DetailsFrame();
	_pageSearch = new SearchFrame();
	_pageDetails = new DetailsFrame();

	_widgetContainer->addWidget(_pageCategories);
	_widgetContainer->addWidget(_pageSearch);
	_widgetContainer->addWidget(_pageDetails);
	setCentralWidget(_widgetContainer);
	_widgetContainer->setCurrentIndex(0);
}
MainWindow::~MainWindow() {
	_pageCategories->deleteLater();
	_pageSearch->deleteLater();
	_pageDetails->deleteLater();
}
