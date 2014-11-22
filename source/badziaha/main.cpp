#include <qtcore/qfile.h>
#include <QtCore/qstringbuilder.h>
#include <QtCore/qstring.h>
#include <QtCore/qstringlist.h>
#include <QtCore/qtextstream.h>
#include "string_ex.h"
#include <math.h>
#include <fstream>
#include <iostream>
#include <QtWidgets/qapplication.h>
#include "forms/main_window.h"
#include "weather.h"
#include "items.h"
#include "known_stuff.h"

struct Data {
	std::vector<ClothesPtr> clothes;
};

Data all_items;

void processClothes(QStringList* data) {
	ClothesPtr current{ make_ptr(new Clothes{}) };
	while (!data->empty()) {
		auto s = data->front().trimmed();
		data->pop_front();
		if (s == "{") {
			current.reset(new Clothes{});
		}
		else if (s == "}") {
			break;
		}
		else {
			auto ss = s.split("=");
			if (ss.size() == 2) {
				auto name = ss[0].trimmed();
				auto value = ss[1].trimmed();
				if (name == "name") {
					current->setName(value);
				}
				else if (name == "target") {
					current->setTargetBodyPart(fromString(value));
				}
				else if (name == "description") {
					current->setDescription(value);
				}
				else if (name == "icon") {
					current->setIcon(value);
				}
				else if (name == "weight") {
					current->setWeight(value.toFloat());
				}
				else if (name == "technology") {
					current->setTechnologyLevel(value.toFloat());
				}
				else if (name == "wind_protection") {
					current->setWindProtection(value.toFloat());
				}
				else if (name == "water_resistance"){
					current->setWaterResistance(value.toFloat());
				}
				else if (name == "radiation_resistance") {
					current->setRadiationResistance(value.toFloat());
				}
				else if (name == "heat_absorption") {
					current->setHeatRadiationAbsorption(value.toFloat());
				}
				else {
					QString s = "Unexpected parameter " + name + " = " + value;
					auto std_s = toWString(s);
					std::wcerr << std_s << std::endl;
				}
			}
		}
	}
	if (!current.get())
		return;

	all_items.clothes.push_back(std::move(current));
}

int main(int argc, char** argv) {
	QApplication app(argc, argv);
	Temperature::instance();
	createStuff();
	QFile file{ ":/config.ini" };
	QTextStream stream{ &file };
	if (file.open(QIODevice::ReadOnly)) {
		auto data = stream.readAll().split("\n");
		while (!data.isEmpty()) {
			auto v = data.front().trimmed();
			data.pop_front();
			auto type = ItemClassTypeFromString(v);
			if (type == ItemClassType::Clothes)
				processClothes(&data);
		}
	}
	MainWindow w;
	w.show();
	return app.exec();
}