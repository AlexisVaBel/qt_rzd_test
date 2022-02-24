#include "NetworkLoader.h"

#include <chrono>
#include <thread>

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QPixmap>
#include <QThread>
#include <QUrl>

using namespace utils::network;

namespace {
static constexpr int64_t SLEEP_DURATION = 200;
static constexpr int64_t NOT_FOUND_CODE = 302;
} // namespace

NetworkLoader::NetworkLoader()
	: _manager(new QNetworkAccessManager(this)) {
	//_manager lives in a thread not equal to run thread - so use signals slots
	connect(_manager, &QNetworkAccessManager::finished, this, &NetworkLoader::onNetworkResult, Qt::QueuedConnection);

	// TODO(me) replace capture this to _manager
	connect(this, &NetworkLoader::setCurrentUrl, this, [this](QString strUrl) {
		QNetworkRequest request;
		request.setUrl(QUrl(strUrl));
		_manager->get(request);
	});
}

NetworkLoader::~NetworkLoader() {
	_manager->deleteLater();
}

void NetworkLoader::run() {
	while (_isWorking) {
		if (_tasks.empty() || _isBusy) {
			std::this_thread::sleep_for(std::chrono::microseconds(SLEEP_DURATION));
		} else {
			{
				_isBusy = true;
				std::lock_guard<std::mutex> guard(_mutex);
				std::tie(_index, _path) = _tasks.front();
				_tasks.pop();
			}

			setCurrentUrl(_path);
		}
	}
	qDebug() << "seems to be stoped";
}

void NetworkLoader::onNetworkResult(QNetworkReply* reply) {
	int httpStatusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
	qDebug() << "some reply here " << reply->error() << "|" << httpStatusCode;

	if (reply->error() || httpStatusCode == NOT_FOUND_CODE) {
		qDebug() << "error : " << reply->errorString();
		_isBusy = false;
		return;
	}
	_pixmap = new QPixmap();
	_pixmap->loadFromData(reply->readAll());
	emit onLoadedImg(_path, _pixmap, _index);
	_isBusy = false;
}

void NetworkLoader::addTask(QString strPath, QPersistentModelIndex index) {
	std::lock_guard<std::mutex> guard(_mutex);
	_tasks.push(std::make_pair(index, strPath));
}

void NetworkLoader::clearTasks() {
	std::lock_guard<std::mutex> guard(_mutex);
	while (!_tasks.empty()) {
		_tasks.pop();
	}
}

void NetworkLoader::stop() {
	_isWorking = false;
}
