//
// Created by abel on 24.02.2022.
//

#include "DetailsFrame.h"
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>
#include <QTableWidget>
#include <QVBoxLayout>
using namespace ui::application;

DetailsFrame::DetailsFrame(QWidget* parent)
	: IFramePage(parent) {
	construct();
}

DetailsFrame::~DetailsFrame() {
}

void DetailsFrame::activate() {
}
void DetailsFrame::waitUpdated() {
}
void DetailsFrame::updatedFinished() {
}

void DetailsFrame::construct() {
	QVBoxLayout* layout = new QVBoxLayout(this);
	layout->setAlignment(Qt::AlignTop);
	setLayout(layout);

	QLineEdit* edit = new QLineEdit(this);
	edit->setProperty("search", true);

	layout->addWidget(edit);
}

void DetailsFrame::appendText(QString text) {
}
void DetailsFrame::appendPixmap(QPixmap* pixmap) {
}
