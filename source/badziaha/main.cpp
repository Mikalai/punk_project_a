#include <math.h>
#include <iostream>
#include <QtWidgets/qapplication.h>
#include "forms/main_window.h"
#include "weather.h"
#include "known_stuff.h"

int main(int argc, char** argv) {
	QApplication app(argc, argv);
	Temperature::instance();
	createStuff();
	MainWindow w;
	w.show();
	return app.exec();
}