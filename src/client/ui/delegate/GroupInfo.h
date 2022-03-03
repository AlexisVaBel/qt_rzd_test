#pragma once
#include <QFrame>
#include <QLabel>
#include <QTableWidget>

namespace ui::delegate {

class GroupInfo : public QFrame {
	Q_OBJECT
protected:
	void resizeEvent(QResizeEvent* event) override;
	using Super = QFrame;

public:
	explicit GroupInfo(QFrame* frame = nullptr);
	void setHeader(QString stringHeader);
	void appendPixmap(QPixmap* pixmap, QString info);
signals:
	void _clickedItem(QString string);

private:
	QTableWidget* _table;
	QLabel* _header;

	int _col{0};
};
} // namespace ui::delegate
