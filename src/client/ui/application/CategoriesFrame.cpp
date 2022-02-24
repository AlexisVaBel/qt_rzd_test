//
// Created by abel on 24.02.2022.
//

#include "CategoriesFrame.h"
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>
#include <QTableWidget>
#include <QVBoxLayout>
using namespace ui::application;

CategoriesFrame::CategoriesFrame(QWidget* parent)
	: IFramePage(parent) {
	construct();
}

CategoriesFrame::~CategoriesFrame() {
}

void CategoriesFrame::activate() {
}
void CategoriesFrame::waitUpdated() {
}
void CategoriesFrame::updatedFinished() {
}

void CategoriesFrame::construct() {
	QVBoxLayout* layout = new QVBoxLayout(this);
	layout->setAlignment(Qt::AlignTop);
	setLayout(layout);

	QLineEdit* edit = new QLineEdit(this);
	edit->setProperty("search", true);

	layout->addWidget(edit);
}

void CategoriesFrame::appendText(QString text) {
}
void CategoriesFrame::appendPixmap(QPixmap* pixmap) {
}
