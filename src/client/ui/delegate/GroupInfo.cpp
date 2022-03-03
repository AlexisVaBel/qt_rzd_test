#include "GroupInfo.h"
#include <QDebug>
#include <QHeaderView>
#include <QPainter>
#include <QPen>
#include <QVBoxLayout>

using namespace ui::delegate;

namespace {
static const int scMaxCol = 3;
}

GroupInfo::GroupInfo(QFrame* frame)
	: Super(frame)
	, _table(new QTableWidget(this))
	, _header(new QLabel(this)) {
	QVBoxLayout* layout = new QVBoxLayout(this);
	setLayout(layout);
	layout->addWidget(_header);
	layout->addWidget(_table);

	_table->setColumnCount(scMaxCol);
	_table->setRowCount(1);

	_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	_table->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	_table->horizontalHeader()->setVisible(false);
	_table->verticalHeader()->setVisible(false);
	_table->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	connect(_table, &QTableWidget::cellClicked, [this](int x, int y) {
		emit _clickedItem(QString("item x y"));
	});
}

void GroupInfo::setHeader(QString stringHeader) {
	_header->setText(std::move(stringHeader));
}

void GroupInfo::appendPixmap(QPixmap* pixmap, QString info) {
	QImage image = pixmap->toImage();
	QPainter p(&image);
	p.setPen(QPen(Qt::white));
	p.setFont(QFont("Roboto", 16, QFont::Bold));
	p.drawText(image.rect(), Qt::AlignCenter, info);

	QImage scaledImage = image.scaled(_table->columnWidth(_col), _table->columnWidth(_col) / 2, Qt::KeepAspectRatioByExpanding);

	QLabel* lbl = new QLabel(this);

	lbl->setPixmap(QPixmap::fromImage(scaledImage));
	lbl->setScaledContents(true);

	_table->setCellWidget(_table->rowCount() - 1, _col++, lbl);

	if (_col > 2) {
		_col = 0;
		_table->insertRow(_table->rowCount() + 1);
	}
}

void GroupInfo::resizeEvent(QResizeEvent* event) {
	_table->resize(this->width(), this->width() * 2 / 3);
	QWidget::resizeEvent(event);
}
