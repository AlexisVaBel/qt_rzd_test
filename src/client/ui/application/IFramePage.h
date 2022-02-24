#pragma once
#include <QFrame>

class IFramePage : public QFrame {
	Q_OBJECT
public:
	IFramePage(QWidget* parent = nullptr)
		: QFrame(parent){};
	virtual ~IFramePage(){};
	virtual void activate() = 0;
	virtual void waitUpdated() = 0;
	virtual void updatedFinished() = 0;
	virtual void construct() = 0;
	virtual void appendText(QString text) = 0;
	virtual void appendPixmap(QPixmap* pixmap) = 0;

signals:
	void searchCalled(QString searchString);
	void itemSelected(int item);

private:
};