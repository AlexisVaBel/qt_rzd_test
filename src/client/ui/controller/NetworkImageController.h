//
// Created by belyeav on 24.02.2022.
//

#pragma once

#include <QObject>

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
	void stop();
	void clearPixmaps();
	std::vector<QPixmap*> getPixmaps() const;
signals:
	void imageLoaded(QPixmap* pix);

private:
	utils::network::NetworkLoader* _netLoader;
	std::vector<QPixmap*> _pixmaps;
};

} // namespace ui::controller
