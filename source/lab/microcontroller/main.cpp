#include <QtWidgets/qapplication.h>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	MainWindow window;
#if defined(Q_OS_SYMBIAN)
	window.showMaximized();
#elif defined(Q_WS_MAEMO_5) || defined(Q_WS_SIMULATOR)
	window.show();
#else
	window.resize(1024, 768);
	window.show();
#endif
	return app.exec();
}

