//
// Created by abel on 24.02.2022.
//
#include "IFramePage.h"
#include <QVBoxLayout>

#pragma once
namespace ui::application {

class SummaryFrame : public IFramePage {
public:
	SummaryFrame(QWidget* parent = nullptr);
	~SummaryFrame() override;
	void activate() override;
	void waitUpdated() override;
	void updatedFinished() override;
	void construct() override;
	void appendText(QString text) override;
	void appendPixmap(QPixmap* pixmap) override;

private:
	QVBoxLayout* _layoutMain;
	std::vector<QGridLayout*> _layoutData;
	int _icol{0};
	int _irow{0};
};

} // namespace ui::application
