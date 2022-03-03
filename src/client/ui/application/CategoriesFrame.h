#include "QWidget"
#include <entity/IConfigProducer.h>
#include <memory>
#include <QListView>
#include <QVBoxLayout>
#include <ui/controller/NetworkImageController.h>

#pragma once
namespace ui::application {

class CategoriesFrame : public QFrame {
public:
	CategoriesFrame(QString pathConfig = "", QWidget* parent = nullptr);
	~CategoriesFrame();

protected:
	void closeEvent(QCloseEvent* event) override;

private:
	void _construct();
	void _updateData();
	void _callSearch();

	// frame widgets
	QListView* _listView;
	QStringList _listData;
	QVBoxLayout* _layoutMain;
	QLineEdit* _edit;
	std::shared_ptr<client::entity::IConfigProducer> _config;
	std::shared_ptr<ui::controller::NetworkImageController> _netLoader;
};

} // namespace ui::application
