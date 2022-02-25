//
// Created by belyeav on 24.02.2022.
//

#include "NetworkImageController.h"
#include <QPixmap>
#include <QThreadPool>
#include <utils/network/NetworkLoader.h>

#include <QDebug>
#include <QLabel>
using namespace ui::controller;

namespace {
static constexpr int WAIT_FOR_DONE_MS = 100;
}

NetworkImageController::NetworkImageController() {
	_netLoader = new utils::network::NetworkLoader();
	_netLoader->setAutoDelete(true);
	//	connect(_netLoader.get(), &utils::network::NetworkLoader::onLoadedImg, this, &NetworkImageController::onLoadedImg);
	connect(_netLoader, &utils::network::NetworkLoader::onLoadedImg, this, &NetworkImageController::onLoadedImg);

	qDebug() << "adding to pool";
	//	QThreadPool::globalInstance()->start(_netLoader.get());
	QThreadPool::globalInstance()->start(_netLoader);
	qDebug() << "added to pool";
}

NetworkImageController::~NetworkImageController() {
	stop();
	_pixmaps.erase(std::remove_if(_pixmaps.begin(), _pixmaps.end(), [](QPixmap* pixmap) { return true; }), _pixmaps.end());
}

void NetworkImageController::clearPixmaps() {
	_pixmaps.erase(std::remove_if(_pixmaps.begin(), _pixmaps.end(), [](QPixmap* pixmap) { return true; }), _pixmaps.end());
}

std::vector<QPixmap*> NetworkImageController::getPixmaps() const {
	return _pixmaps;
}

void NetworkImageController::addUrl(QString path) {
	qDebug() << "add url " << path;
	_netLoader->addTask(std::move(path), QPersistentModelIndex());
}

void NetworkImageController::onLoadedImg(const QString& path, QPixmap* pix, const QPersistentModelIndex& index) {
	qDebug() << "loaded by path: " << path;
	_pixmaps.push_back(std::move(pix));
	imageLoaded(*_pixmaps.rbegin());
}

void NetworkImageController::stop() {
	_netLoader->stop();
	QThreadPool::globalInstance()->waitForDone(WAIT_FOR_DONE_MS);
}
