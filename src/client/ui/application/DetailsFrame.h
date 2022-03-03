#pragma once

#include "IFramePage.h"
#include <QPushButton>
#include <QStackedWidget>

namespace ui::application {

class DetailsFrame : public IFramePage {
public:
	DetailsFrame(QWidget* parent = nullptr);
	~DetailsFrame() override;
	void imageLoaded(QPixmap* pixmap) override;
	void groupFinished(QString groupName) override;
	void processText(QString string) override;

private:
	void _construct();
	QStackedWidget* _stackedImage;
	QPushButton* _btnPrevious;
	QPushButton* _btnNext;
};

} // namespace ui::application
