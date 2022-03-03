#pragma once
#include <memory>
#include <QFrame>

#include "ui/controller/NetworkImageController.h"
#include <entity/IConfigProducer.h>

namespace ui::application {

class IFramePage : public QFrame {
	Q_OBJECT
protected:
	void showEvent(QShowEvent* event) override {
		emit frameIsActivated(_frameName);
		QWidget::showEvent(event);
	}

public:
	IFramePage(QWidget* parent = nullptr)
		: QFrame(parent){};

	virtual ~IFramePage(){};

	virtual void setName(QString name) {
		_frameName = std::move(name);
	}

	virtual void setConfigProducer(std::shared_ptr<client::entity::IConfigProducer> config) {
		_config = config;
	}

	virtual void setNetworkLoader(std::shared_ptr<ui::controller::NetworkImageController> netLoader) {
		_netLoader = netLoader;
		connect(_netLoader.get(), &ui::controller::NetworkImageController::imageLoaded, this, &IFramePage::imageLoaded);
		connect(_netLoader.get(), &ui::controller::NetworkImageController::groupFinished, this, &IFramePage::groupFinished);
	}

	virtual void imageLoaded(QPixmap* pixmap) = 0;
	virtual void groupFinished(QString groupName) = 0;
	virtual void processText(QString string) = 0;

signals:
	void searchCalled(QString searchString);
	void frameIsActivated(QString frameName);

protected:
	std::shared_ptr<client::entity::IConfigProducer> _config;
	std::shared_ptr<ui::controller::NetworkImageController> _netLoader;

private:
	QString _frameName{};
};
} // namespace ui::application
