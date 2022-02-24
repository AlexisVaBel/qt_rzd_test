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
}
void SearchFrame::updatedFinished() {
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

	frameContainerSearch->setLayout(layoutSearch);
	layoutSearch->addWidget(edit);
	layoutSearch->addWidget(buttonSearch);

	QListView* list = new QListView(this);
	list->setSelectionMode(QAbstractItemView::SingleSelection);

	QStringListModel* lstModel = new QStringListModel(this);
	QStringList lst;
	lst << "1 some text"
		<< "2"
		<< "3";
	lstModel->setStringList(lst);

	list->setModel(lstModel);

	layout->addWidget(labelSearch);
	layout->addWidget(frameContainerSearch);
	layout->addWidget(list);
}

void SearchFrame::appendText(QString text) {
	//
}

void SearchFrame::appendPixmap(QPixmap* pixmap) {
	//
}
