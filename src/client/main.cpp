#include <QApplication>
#include <QQmlApplicationEngine>

#include <QDebug>
#include <QThread>

#include <ui/controller/GameController.h>

#include "ui/application/MainWindow.h"
#include "ui/controller/NetworkImageController.h"
#include "ui/model/GameBoard.h"

static constexpr auto USAGE =
		R"(RZD Test work.

    Usage:
          TODO - prepare usage
 Options:
          -h --help     Show this screen.
          --version     Show version.
)";

int main(int argc, char** argv) {
	//	SPDLOG_INFO("initiated app");

	QApplication app(argc, argv);
	qDebug() << "init thread id " << QThread::currentThreadId();

	//	SPDLOG_INFO("initiated qml engine");
	ui::controller::NetworkImageController controller;
	controller.addUrl("https://www.rzd.ru/api/media/resources/1787985");
	controller.addUrl("https://www.rzd.ru/api/media/resources/1797111");
	controller.addUrl("https://www.rzd.ru/api/media/resources/1761235");
	controller.addUrl("https://www.rzd.ru/api/media/resources/1784814");
	controller.addUrl("https://www.rzd.ru/api/media/resourcess/1707466");
	controller.addUrl("https://www.rzd.ru/api/media/resources/1787985");
	controller.addUrl("https://www.rzd.ru/api/media/resources/1707466");
	controller.stop();

	MainWindow mainWindow;
	mainWindow.show();

	return app.exec();
}

//	model::GameBoard board;
//	qmlRegisterType<model::GameBoard>("Game", 1, 0, "GameBoardModel");
//
//	ui::controller::GameController gameController;
//	qmlRegisterType<ui::controller::GameController>("GameController", 1, 0, "GameController");

//	QQmlApplicationEngine engine;
//
//	const QUrl qmlUrl(QStringLiteral("qrc:/ui/qml/main.qml"));
//	engine.load(qmlUrl);
//
//	QObject::connect(&engine, &QQmlApplicationEngine::objectCreated, &app, [qmlUrl](QObject* object, const QUrl& objUrl) {
//		if (!object || qmlUrl == objUrl) {
//			QCoreApplication::exit(EXIT_FAILURE);
//		}
//	});
