#include <QApplication>

#include "ui/application/MainWindow.h"

int main(int argc, char** argv) {
	QApplication app(argc, argv);
	QString str{""};
	if (argc > 1) {
		str = argv[1];
	} else {
		str = "./test.json";
	}
	ui::application::MainWindow mainWindow(nullptr, str);
	mainWindow.setWindowState(Qt::WindowMaximized);
	mainWindow.show();

	return app.exec();
}
