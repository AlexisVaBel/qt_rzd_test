#include "GameController.h"
#include <QDebug>

using namespace ui::controller;

GameController::GameController(QObject* parent)
	: QObject(parent) {
}

bool GameController::nextStep() {
	++_stepCount;
	qDebug() << "__step__" << _stepCount;
	return true;
}

void GameController::startProcess() {
	qDebug() << "__started__";
}
void GameController::finishProcess() {
	qDebug() << "__finished with__" << _stepCount;
}
