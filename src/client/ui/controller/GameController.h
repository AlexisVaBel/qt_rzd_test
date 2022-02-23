#pragma once
#include "IController.h"
#include <QObject>

namespace ui::controller {
class GameController : public QObject, IController {
	Q_OBJECT

	Q_PROPERTY(int stepCount READ stepCount CONSTANT)
public:
	explicit GameController(QObject* parent = nullptr);

	void startProcess() override;
	void finishProcess() override;

	int stepCount() const {
		return _stepCount;
	}

	Q_INVOKABLE bool nextStep();

private:
	int _stepCount{0};
};
} // namespace ui::controller
