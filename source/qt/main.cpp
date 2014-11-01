#include <thread>
#include <QtWidgets/QWidget>
#include <QtWidgets/QApplication>
#include <config.h>
#include "module.h"
class QWidget;

using namespace Punk::Engine;

int g_argc;
char** g_argv;
std::thread g_qt_thread;

extern "C" PUNK_ENGINE_API void RunGuiThread(Core::Pointer<Gui::IWidget> (*func)()) {
	QApplication a(g_argc, g_argv);
	auto w = func();
	w->Show();
	a.exec();
}

int main(int argc, char *argv[])
{	
	g_argc = argc;
	g_argv = argv;

	RunGuiThread([]() -> Core::Pointer<Gui::IWidget> {
		auto tab_holder = Core::Pointer < Gui::ITabHolder > {Punk::Engine::Qt::CreateTabHolder(), Core::DestroyObject};
		auto tab = Core::Pointer < Gui::IObjectTab > {Punk::Engine::Qt::CreateIObjectTab(), Core::DestroyObject};
		tab->SetObject(tab_holder);
		tab_holder->AddTab("Object", tab);
		return tab_holder; 
	});
}
