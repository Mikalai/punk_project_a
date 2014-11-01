#include <QtWidgets/qapplication.h>
#include "main_form.h"

int main(int argc, char** argv) {
	QApplication app(argc, argv);
	MainWindow w;
	w.show();
	return app.exec();
}