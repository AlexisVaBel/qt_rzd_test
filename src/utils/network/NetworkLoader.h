//
// Created by belyeav on 24.02.2022.
//

#pragma once
#include <mutex>
#include <QObject>
#include <QPersistentModelIndex>
#include <QRunnable>
#include <queue>

class QNetworkAccessManager;
class QNetworkReply;

namespace utils::network {
class NetworkLoader : public QObject
	, public QRunnable {
	Q_OBJECT
public:
	NetworkLoader();
	~NetworkLoader();
	void run();
	void addTask(QString strPath, QPersistentModelIndex index);
	void clearTasks();
	void stop();

signals:
	void onLoadedImg(const QString& path, QPixmap* pix, const QPersistentModelIndex& index);
	void setCurrentUrl(QString strUrl);

private:
	void onNetworkResult(QNetworkReply* reply);

	QPixmap* _pixmap{nullptr};
	QString _path;
	QPersistentModelIndex _index;
	QNetworkAccessManager* _manager{nullptr};
	bool _isWorking{true};
	bool _isBusy{false};

	std::mutex _mutex;
	std::queue<std::pair<QPersistentModelIndex, QString>> _tasks;
};

} // namespace utils::network
