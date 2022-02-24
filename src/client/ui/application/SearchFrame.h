//
// Created by abel on 24.02.2022.
//
#include "IFramePage.h"

#pragma once
namespace ui::application {

class SearchFrame : public IFramePage {
public:
	SearchFrame(QWidget* parent = nullptr);
	~SearchFrame() override;
	void activate() override;
	void waitUpdated() override;
	void updatedFinished() override;
	void construct() override;
	void appendText(QString text) override;
	void appendPixmap(QPixmap* pixmap) override;
};

} // namespace ui::application
