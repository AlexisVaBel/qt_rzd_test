#include "IFramePage.h"
#include <QLineEdit>
#include <QScrollArea>
#include <QTableView>
#include <QVBoxLayout>
#include <ui/delegate/GroupInfo.h>

#pragma once
namespace ui::application {

class SummaryFrame : public IFramePage {
	using Self = SummaryFrame;
	using Super = IFramePage;

public:
	SummaryFrame(QWidget* parent = nullptr);
	~SummaryFrame() override;
	void imageLoaded(QPixmap* pixmap) override;
	void groupFinished(QString groupName) override;
	void processText(QString string) override;

private:
	void _callSearch(QString strSearch);
	bool _searchSuccess(QString const& shortName, QString const& title, QString const& content);
	void _construct();
	void _updateData(QString);
	void _clearCards();
	void _initCard();

protected:
	void resizeEvent(QResizeEvent* event) override;

private:
	QVBoxLayout* _layoutMain;
	QScrollArea* _scroll;
	QFrame* _frameContainer;

	QLineEdit* _edit;
	std::vector<ui::delegate::GroupInfo*> _infoCards;
};

} // namespace ui::application
