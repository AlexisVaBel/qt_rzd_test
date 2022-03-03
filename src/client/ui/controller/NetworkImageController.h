//
// Created by belyeav on 24.02.2022.
//

#pragma once

#include <QObject>
#include <queue>

namespace utils::network {
class NetworkLoader;
}

class QPixmap;

namespace ui::controller {
class NetworkImageController : public QObject {
	Q_OBJECT
public:
	NetworkImageController();
	~NetworkImageController();
	void onLoadedImg(const QString& path, QPixmap* pix, const QPersistentModelIndex& index);
	void addUrl(QString path);
	void addGroupName(QString groupName, int expectedImages);
	void stop();
	void clearPixmaps();
	std::vector<QPixmap*> getPixmaps() const;
signals:
	void imageLoaded(QPixmap* pix);
	void groupFinished(QString groupName);

private:
	utils::network::NetworkLoader* _netLoader;
	std::vector<QPixmap*> _pixmaps;

	struct GroupImages {
		QString name;
		int count;
	};
	std::queue<GroupImages> _groups;
	int _groupImageCounter{0};
};

} // namespace ui::controller
