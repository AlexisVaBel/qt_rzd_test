#include "MainWindow.h"
#include "DetailsFrame.h"

#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVBoxLayout>

#include "SearchFrame.h"
#include "SummaryFrame.h"
#include <entity/Route.h>
#include <entity/RoutesAgregate.h>
#include <utils/json/JsonLoader.h>

using namespace ui::application;

MainWindow::MainWindow(QWidget* parent, QString pathConfig)
	: Super(parent)
	, _jsonLoader(std::make_unique<utils::json::JsonLoader>(pathConfig))
	, _controller(std::make_unique<ui::controller::NetworkImageController>())
	, _routesAgregate(std::make_unique<client::entity::RoutesAgregate>())
	, _widgetContainer(new QStackedWidget(this)) {
	QFile styleFile(":/app.qss");
	styleFile.open(QFile::OpenModeFlag::ReadOnly);
	QString const styleSheet(styleFile.readAll());
	setStyleSheet(styleSheet);

	connect(_controller.get(), &ui::controller::NetworkImageController::imageLoaded, this, &Self::_onImageLoaded);

	_constructFrames();

	if (_jsonLoader->isFileValid()) {
		QJsonDocument document = _jsonLoader->load();
		_routesAgregate->read(document.object());
	} else {
		qDebug() << ("file is not readable... ");
	}
}

MainWindow::~MainWindow() {
}

void MainWindow::_constructFrames() {
	_pageSummary = new SummaryFrame(this);
	_pageCategories = new SearchFrame(this);
	_pageDetails = new DetailsFrame(this);
	_pageSummary->setName("categories");
	_pageCategories->setName("summary");
	_pageDetails->setName("full");
	connect(_pageDetails, &IFramePage::frameIsActivated, this, &Self::_frameIsActivated);
	connect(_pageCategories, &IFramePage::frameIsActivated, this, &Self::_frameIsActivated);
	connect(_pageSummary, &IFramePage::frameIsActivated, this, &Self::_frameIsActivated);

	_widgetContainer->addWidget(_pageSummary);
	_widgetContainer->addWidget(_pageCategories);
	_widgetContainer->addWidget(_pageDetails);
	_widgetContainer->setCurrentIndex(0);

	QFrame* frameContainer = new QFrame(this);
	QVBoxLayout* layoutContainer = new QVBoxLayout(frameContainer);

	// controls to move along frames
	QHBoxLayout* layoutControls = new QHBoxLayout(frameContainer);
	_btnPrevious = new QPushButton("⇦", this);
	_btnNext = new QPushButton("⇨", this);
	_btnPrevious->setMinimumHeight(32);
	_btnNext->setMinimumHeight(32);
	_btnPrevious->setProperty("navigate", true);
	_btnNext->setProperty("navigate", true);
	layoutControls->setAlignment(Qt::AlignRight);
	layoutControls->addWidget(_btnPrevious);
	layoutControls->addWidget(_btnNext);

	connect(_btnPrevious, &QPushButton::clicked, this, &Self::_previousFrame);
	connect(_btnNext, &QPushButton::clicked, this, &Self::_nextFrame);
	//~ controls to move along frames

	// container for buttons and stackedwidget(_widgetContainer)
	layoutContainer->setAlignment(Qt::AlignTop);
	layoutContainer->addWidget(_widgetContainer);
	layoutContainer->addLayout(layoutControls);
	frameContainer->setLayout(layoutContainer);

	setCentralWidget(frameContainer);
}

void MainWindow::_previousFrame() {
	int currentIndex = _widgetContainer->currentIndex();
	if (currentIndex > 0) {
		_widgetContainer->setCurrentIndex(--currentIndex);
	}
}

void MainWindow::_nextFrame() {
	int currentIndex = _widgetContainer->currentIndex();
	if (currentIndex < _widgetContainer->count()) {
		_widgetContainer->setCurrentIndex(++currentIndex);
	}
}

//some buisness logic wheech need to be replaced from here
void MainWindow::_frameIsActivated(QString frameName) {
	_controller->clearPixmaps();
	if (frameName == "categories") {
		auto vct = _routesAgregate->getCategories();
		_pageCategories->waitUpdated();
		for (auto const& str : vct) {
			_pageCategories->appendText(str);
		}
		_pageCategories->updatedFinished();
	}
	if (frameName == "full") {
		// pram pam pam
	}
	if (frameName == "summary") {
		auto vct = _routesAgregate->getCategories();
//		_controller->clearPixmaps();
		// tests for loading
//		_controller->addUrl("https://www.rzd.ru/api/media/resources/1787985");
//		_controller->addUrl("https://www.rzd.ru/api/media/resources/1797111");
//		_controller->addUrl("https://www.rzd.ru/api/media/resources/1761235");
//		_controller->addUrl("https://www.rzd.ru/api/media/resources/1784814");
//		_controller->addUrl("https://www.rzd.ru/api/media/resourcess/1707466");
//		_controller->addUrl("https://www.rzd.ru/api/media/resources/1787985");
//		_controller->addUrl("https://www.rzd.ru/api/media/resources/1707466");
		//~tests for loading
		_pageSummary->waitUpdated();
		for (auto const& str : vct) {
			_pageSummary->appendText(str);
		}
		_pageSummary->updatedFinished();
	}
}

void MainWindow::_onImageLoaded(QPixmap* pixmap) {
	qobject_cast<IFramePage*>(_widgetContainer->currentWidget())->appendPixmap(pixmap);
}
