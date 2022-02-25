#pragma once
#include "entity/RoutesAgregate.h"
#include "IFramePage.h"
#include <memory>
#include <QMainWindow>
#include <QStackedWidget>

#include <QPushButton>
#include <ui/controller/NetworkImageController.h>
#include <utils/json/JsonLoader.h>

namespace ui::application {
class MainWindow : public QMainWindow {
	Q_OBJECT
	using Self = MainWindow;
	using Super = QMainWindow;

public:
	MainWindow(QWidget* parent = nullptr, QString pathConfig = "");
	~MainWindow() override;

private:
	void _frameIsActivated(QString frameName);
	void _constructFrames();
	void _previousFrame();
	void _nextFrame();
	void _onImageLoaded(QPixmap* pixmap);

	std::unique_ptr<utils::json::JsonLoader> _jsonLoader;
	std::unique_ptr<ui::controller::NetworkImageController> _controller;
	std::unique_ptr<client::entity::RoutesAgregate> _routesAgregate;

	QPushButton* _btnPrevious;
	QPushButton* _btnNext;

	IFramePage* _pageSummary{nullptr};
	IFramePage* _pageCategories{nullptr};
	IFramePage* _pageDetails{nullptr};

	QStackedWidget* _widgetContainer;
};
} // namespace ui::application
