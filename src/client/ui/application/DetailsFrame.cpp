#include "DetailsFrame.h"
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>

#include <QDebug>
using namespace ui::application;

DetailsFrame::DetailsFrame(QWidget* parent)
	: IFramePage(parent)
	, _stackedImage(new QStackedWidget(this)) {
	_construct();
}

DetailsFrame::~DetailsFrame() {
}

void DetailsFrame::_construct() {
	QVBoxLayout* layout = new QVBoxLayout(this);
	layout->setAlignment(Qt::AlignTop);
	setLayout(layout);

	QLabel* labelInfo = new QLabel("Info", this);
	QTextEdit* editDetail = new QTextEdit(this);
	editDetail->setText("detailed");
	editDetail->setReadOnly(true);

	QFrame* frameContainer = new QFrame(this);
	QVBoxLayout* layoutContainer = new QVBoxLayout(frameContainer);

	QHBoxLayout* layoutControls = new QHBoxLayout(frameContainer);
	_btnPrevious = new QPushButton("prev", this);
	_btnNext = new QPushButton("next", this);
	_btnPrevious->setMinimumHeight(32);
	_btnNext->setMinimumHeight(32);
	_btnPrevious->setProperty("navigate", true);
	_btnNext->setProperty("navigate", true);
	layoutControls->setAlignment(Qt::AlignRight);
	layoutControls->addWidget(_btnPrevious);
	layoutControls->addWidget(_btnNext);

	layoutContainer->addWidget(_stackedImage);
	layoutContainer->addLayout(layoutControls);

	layout->addWidget(labelInfo);
	layout->addWidget(editDetail);
	layout->addWidget(frameContainer);
}

void DetailsFrame::imageLoaded(QPixmap* pixmap) {
	if (this->isVisible()) {
		qDebug() << __PRETTY_FUNCTION__;
	}
}

void DetailsFrame::groupFinished(QString groupName) {
	//
}

void DetailsFrame::processText(QString string) {
	//
}
