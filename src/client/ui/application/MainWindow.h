#pragma once
#include "IFramePage.h"
#include <memory>
#include <QMainWindow>
#include <QStackedWidget>

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
	void constructFrames();

	std::unique_ptr<utils::json::JsonLoader> _jsonLoader;
	std::unique_ptr<ui::controller::NetworkImageController> _controller;

	IFramePage* _pageCategories{nullptr};
	IFramePage* _pageSearch{nullptr};
	IFramePage* _pageDetails{nullptr};

	QStackedWidget* _widgetContainer;
};
} // namespace ui::application
