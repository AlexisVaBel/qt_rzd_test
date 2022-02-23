#include <QApplication>
#include <QQmlApplicationEngine>

#include "spdlog/sinks/stdout_sinks.h"
#include <spdlog/spdlog.h>

#include <ui/controller/GameController.h>

#include "ui/model/GameBoard.h"

static constexpr auto USAGE =
		R"(RZD Test work.

    Usage:
          TODO - prepare usage
 Options:
          -h --help     Show this screen.
          --version     Show version.
)";

auto initLog() {
	auto console = spdlog::stdout_logger_mt("console");
	spdlog::set_default_logger(console);
	spdlog::set_pattern("[source %s] [function %!] [line %#] %v");
	return console;
}

int main(int argc, char** argv) {
	SPDLOG_INFO("initiated app");

	QApplication app(argc, argv);

	//	model::GameBoard board;
	//	qmlRegisterType<model::GameBoard>("Game", 1, 0, "GameBoardModel");
	//
	//	ui::controller::GameController gameController;
	//	qmlRegisterType<ui::controller::GameController>("GameController", 1, 0, "GameController");

	SPDLOG_INFO("initiated qml engine");
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

	return app.exec();
}
