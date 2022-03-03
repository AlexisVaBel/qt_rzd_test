#include "SummaryFrame.h"
#include "DetailsFrame.h"
#include "entity/Route.h"
#include <QDebug>

#include <QLabel>
#include <QLineEdit>

#include <QPainter>
#include <QVBoxLayout>

using namespace ui::application;
namespace {
static constexpr int COL_COUNT = 3;
}
SummaryFrame::SummaryFrame(QWidget* parent)
	: IFramePage(parent)
	, _layoutMain(new QVBoxLayout(this))
	, _scroll(new QScrollArea(this))
	, _frameContainer(new QFrame(_scroll))
	, _edit(new QLineEdit(this)) {
	_construct();
	connect(this, &IFramePage::frameIsActivated, this, &Self::_updateData);
}

SummaryFrame::~SummaryFrame() {
}

void SummaryFrame::_construct() {
	QVBoxLayout* layoutScroll = new QVBoxLayout(_frameContainer);
	layoutScroll->setAlignment(Qt::AlignTop);
	_frameContainer->setLayout(layoutScroll);

	_edit->setProperty("search", true);
	_edit->setPlaceholderText("enter your text");

	_layoutMain->setAlignment(Qt::AlignTop);
	_layoutMain->addWidget(_edit);
	_layoutMain->addWidget(_scroll);

	_scroll->setAlignment(Qt::AlignTop);
	_scroll->setWidget(_frameContainer);
	_scroll->setWidgetResizable(true);

	setLayout(_layoutMain);
}

bool SummaryFrame::_searchSuccess(QString const& shortName, QString const& title, QString const& content) {
	QString searchKey = _edit->text();

	//	Состоит из поля ввода, кнопки Найти и списка найденных объектов. Поиск осуществляется по полям content, title, short_name.
	return (shortName.contains(searchKey) || searchKey.contains(shortName) || title.contains(searchKey) || content.contains(searchKey));
}

void SummaryFrame::_updateData(QString) {
	if (this->isVisible()) {
		_clearCards();
		_initCard();

		auto summaryVct = _config->getRoutes();
		auto categoriesVct = _config->getCategories();
		_netLoader->clearPixmaps();
		QStringList lst;
		for (auto categoryName : categoriesVct) {
			lst.clear();

			auto id = _config->getIdByCategory(categoryName);
			for (auto summary : summaryVct) {
				auto it = std::find(summary._categories.begin(), summary._categories.end(), id);
				if (it != summary._categories.end()) {
					if (_searchSuccess(summary._shortName, summary._title, summary._content)) {
						lst.append(summary._imageSource);
					}
				}
			}

			if (!lst.empty()) {
				_netLoader->addGroupName(categoryName, lst.count());
				for (QString url : lst) {
					_netLoader->addUrl(url);
				}
			}
		}
	}
}

void SummaryFrame::imageLoaded(QPixmap* pixmap) {
	auto it = _infoCards.rbegin();
	if (it == _infoCards.rend()) {
		return;
	}
	(*it)->appendPixmap(pixmap, "somestring");
}

void SummaryFrame::groupFinished(QString groupName) {
	auto it = _infoCards.rbegin();
	if (it == _infoCards.rend()) {
		return;
	}
	(*it)->setHeader(groupName);

	_initCard();
}

void SummaryFrame::processText(QString string) {
	_edit->setText(string);
}

void SummaryFrame::_callSearch(QString strSearch) {
	DetailsFrame* pageDatail = new DetailsFrame();
	pageDatail->setConfigProducer(_config);
	pageDatail->setNetworkLoader(_netLoader);
	pageDatail->processText(_edit->text());
	pageDatail->setAttribute(Qt::WA_DeleteOnClose);
	pageDatail->resize(this->size());
	pageDatail->move(this->pos());
	pageDatail->show();
}

void SummaryFrame::_clearCards() {
	auto it = _infoCards.begin();
	while (it != _infoCards.end()) {
		_frameContainer->layout()->removeWidget(*it);
		(*it)->deleteLater();
		++it;
	}
}

void SummaryFrame::_initCard() {
	_infoCards.emplace_back(new ui::delegate::GroupInfo{_frameContainer});
	auto it = _infoCards.rbegin();

	_frameContainer->layout()->addWidget(*it);
	connect((*it), &ui::delegate::GroupInfo::_clickedItem, this, &Self::_callSearch);
}

void SummaryFrame::resizeEvent(QResizeEvent* event) {
	QWidget::resizeEvent(event);
}
