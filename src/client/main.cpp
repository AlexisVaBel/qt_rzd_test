#include <QApplication>
#include <ui/application/CategoriesFrame.h>

int main(int argc, char** argv) {
	QApplication app(argc, argv);
	QString str{""};
	if (argc > 1) {
		str = argv[1];
	} else {
		str = "./test.json";
	}
	ui::application::CategoriesFrame categoriesFrame(str);
	categoriesFrame.resize(640, 480);
	categoriesFrame.show();
	return app.exec();
}
