//
// Created by abel on 24.02.2022.
//

#include "SearchFrame.h"
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>
#include <QStringListModel>
#include <QTableWidget>
#include <QVBoxLayout>
using namespace ui::application;

SearchFrame::SearchFrame(QWidget* parent)
	: IFramePage(parent) {
	construct();
}

SearchFrame::~SearchFrame() {
}

void SearchFrame::activate() {
}

void SearchFrame::waitUpdated() {
	_listData.clear();
}

void SearchFrame::updatedFinished() {
	QStringListModel* model = qobject_cast<QStringListModel*>(_listView->model());
	model->setStringList(_listData);
}

void SearchFrame::construct() {
	QVBoxLayout* layout = new QVBoxLayout(this);
	layout->setAlignment(Qt::AlignTop);
	setLayout(layout);
	QLabel* labelSearch = new QLabel(this);
	labelSearch->setText("Search");

	QFrame* frameContainerSearch = new QFrame(this);
	frameContainerSearch->setMinimumHeight(180);
	frameContainerSearch->setProperty("container", true);

	QLineEdit* edit = new QLineEdit(this);

	QPushButton* buttonSearch = new QPushButton(this);
	QHBoxLayout* layoutSearch = new QHBoxLayout(frameContainerSearch);
	buttonSearch->setText("Search");

	connect(buttonSearch, &QPushButton::clicked, this, [this, edit] {
		emit searchCalled(edit->text());
	});

	frameContainerSearch->setLayout(layoutSearch);
	layoutSearch->addWidget(edit);
	layoutSearch->addWidget(buttonSearch);

	_listView = new QListView(this);
	_listView->setSelectionMode(QAbstractItemView::SingleSelection);

	QStringListModel* lstModel = new QStringListModel(this);
	_listView->setModel(lstModel);

	layout->addWidget(labelSearch);
	layout->addWidget(frameContainerSearch);
	layout->addWidget(_listView);
}

void SearchFrame::appendText(QString text) {
	_listData.push_back(text);
}

void SearchFrame::appendPixmap(QPixmap* pixmap) {
	//
}
