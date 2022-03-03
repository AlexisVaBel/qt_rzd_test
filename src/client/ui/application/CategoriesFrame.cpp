#include "CategoriesFrame.h"
#include "DetailsFrame.h"
#include "SummaryFrame.h"

#include <entity/RoutesAgregate.h>
#include <utils/json/JsonLoader.h>

#include <QCloseEvent>
#include <QDebug>
#include <QJsonDocument>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QMessageBox>
#include <QPushButton>
#include <QStringListModel>
#include <QVBoxLayout>

using namespace ui::application;

CategoriesFrame::CategoriesFrame(QString pathConfig, QWidget* parent)
	: QFrame(parent) {
	utils::json::JsonLoader jsonLoader(pathConfig);
	_netLoader = std::make_shared<ui::controller::NetworkImageController>();
	_config = std::make_shared<client::entity::RoutesAgregate>();

	QFile styleFile(":/app.qss");
	styleFile.open(QFile::OpenModeFlag::ReadOnly);
	QString const styleSheet(styleFile.readAll());
	setStyleSheet(styleSheet);

	if (jsonLoader.isFileValid()) {
		QJsonDocument document = jsonLoader.load();
		_config->read(document.object());
	} else {
		qDebug() << ("file is not readable... ");
	}

	_construct();
	_updateData();
}

CategoriesFrame::~CategoriesFrame() {
}

void CategoriesFrame::_construct() {
	_layoutMain = new QVBoxLayout(this);
	_layoutMain->setAlignment(Qt::AlignTop);
	setLayout(_layoutMain);

	QLabel* labelSearch = new QLabel(this);
	labelSearch->setText("Search");
	labelSearch->setMinimumHeight(32);

	QFrame* frameContainerSearch = new QFrame(this);
	frameContainerSearch->setMinimumHeight(180);
	frameContainerSearch->setProperty("container", true);

	_edit = new QLineEdit(this);

	QPushButton* buttonSearch = new QPushButton(this);
	QHBoxLayout* layoutSearch = new QHBoxLayout(frameContainerSearch);
	buttonSearch->setText("Найти");

	connect(buttonSearch, &QPushButton::clicked, this, [this] {
		_callSearch();
	});

	frameContainerSearch->setLayout(layoutSearch);
	layoutSearch->addWidget(_edit);
	layoutSearch->addWidget(buttonSearch);

	_listView = new QListView(this);
	_listView->setSelectionMode(QAbstractItemView::SingleSelection);
	_listView->setEditTriggers(QAbstractItemView::NoEditTriggers);

	QStringListModel* lstModel = new QStringListModel(this);
	_listView->setModel(lstModel);

	_layoutMain->addWidget(labelSearch);
	_layoutMain->addWidget(frameContainerSearch);
	_layoutMain->addWidget(_listView);
}

void CategoriesFrame::_updateData() {
	_listData.clear();
	for (QString str : _config->getCategories()) {
		_listData.push_back(str);
	}

	QStringListModel* model = qobject_cast<QStringListModel*>(_listView->model());
	model->setStringList(_listData);
}

void CategoriesFrame::_callSearch() {
	SummaryFrame* pageSummary = new SummaryFrame();
	pageSummary->setConfigProducer(_config);
	pageSummary->setNetworkLoader(_netLoader);
	pageSummary->processText(_edit->text());
	pageSummary->setAttribute(Qt::WA_DeleteOnClose);
	pageSummary->resize(this->size());
	pageSummary->move(this->pos());
	pageSummary->show();
}

void CategoriesFrame::closeEvent(QCloseEvent* event) {
	auto messageResult = QMessageBox::question(this,
			"Выход",
			"Закрыть приложение",
			QMessageBox::Yes | QMessageBox::No,
			QMessageBox::Yes);
	if (messageResult != QMessageBox::Yes) {
		event->ignore();
		return;
	}

	QWidget::closeEvent(event);
}
