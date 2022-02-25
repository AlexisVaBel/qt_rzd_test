#include "SummaryFrame.h"
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>

using namespace ui::application;
namespace {
static constexpr int COL_COUNT = 3;
}
SummaryFrame::SummaryFrame(QWidget* parent)
	: IFramePage(parent) {
	construct();
}

SummaryFrame::~SummaryFrame() {
}

void SummaryFrame::activate() {
}

void SummaryFrame::waitUpdated() {
	_layoutData.erase(std::remove_if(_layoutData.begin(), _layoutData.end(), [](QGridLayout* layout) { return true; }), _layoutData.end());
	for (int i = _layoutMain->count() - 1; i > 0; --i) {
		_layoutMain->removeItem(_layoutMain->itemAt(i));
	}
}

void SummaryFrame::updatedFinished() {
	for (auto& layout : _layoutData) {
		_layoutMain->addLayout(layout);
	}
}

void SummaryFrame::construct() {
	_layoutMain = new QVBoxLayout(this);
	_layoutMain->setAlignment(Qt::AlignTop);
	setLayout(_layoutMain);

	QLineEdit* edit = new QLineEdit(this);
	edit->setProperty("search", true);

	_layoutMain->addWidget(edit);
}

void SummaryFrame::appendText(QString text) {
	_layoutData.emplace_back(new QGridLayout());
	auto ref = _layoutData.rbegin();
	QLabel* summary = new QLabel(text, this);
	summary->setProperty("summary", true);
	(*ref)->addWidget(summary, 0, 0, 1, COL_COUNT);
	_irow = 1;
	_icol = 0;
}

void SummaryFrame::appendPixmap(QPixmap* pixmap) {
	auto ref = _layoutData.rbegin();
	QLabel* summary = new QLabel(this);
	summary->setPixmap(*pixmap);
	(*ref)->addWidget(summary, _irow, ++_icol);
	if (_icol >= COL_COUNT) {
		++_irow;
		_icol = 0;
	}
}
