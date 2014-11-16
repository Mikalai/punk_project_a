#include <QtCore/qfile.h>
#include <QtCore/qtextstream.h>
#include <iostream>
#include "items.h"
#include "string_ex.h"
#include "singletone.h"

class ClothesFactory : public Singletone<ClothesFactory> {
public:
	ClothesFactory() {
		QFile file{ ":/clothes/clothes/config.ini" };
		QTextStream stream{ &file };
		if (file.open(QIODevice::ReadOnly)) {
			std::unique_ptr<Clothes> current{ new Clothes{} };
			while (!stream.atEnd()) {
				auto s = stream.readLine();
				if (s == "{") {
					current.reset(new Clothes{});
				}
				else if (s == "}") {
					m_clothes.push_back(std::move(current));
				}
				else {
					auto ss = s.split("=");
					if (ss.size() == 2) {
						auto name = ss[0];
						auto value = ss[1];
						if (name == "name") {
							current->setName(value);
						}
						else if (name == "description") {
							current->setDescription(value);
						}
						else if (name == "icon") {
							current->setIcon(QImage{ value });
						}
						else if (name == "weight") {
							current->setWeight(value.toFloat());
						}
						else if (name == "technology") {
							current->setTechnologyLevel(value.toFloat());
						}
						else if (name == "wind_protection") {
							current->m_wind_protection = value.toFloat();
						}
						else if (name == "water_resistance"){
							current->m_water_resistance = value.toFloat();
						}
						else if (name == "radiation_resistance") {
							current->m_radiation_resistance = value.toFloat();
						}
						else if (name == "heat_absorption") {
							current->m_heat_radiation_absorption = value.toFloat();
						}
						else {
							QString s = "Unexpected parameter " + name + " = " + value;
							auto std_s = toWString(s);
							std::wcerr << std_s << std::endl;
						}
					}
				}
			}
		}
	}

	int find(QString name) {
		for (int i = 0, max_i = (int)m_clothes.size(); i < max_i; ++i) {
			if (m_clothes[i]->name() == name)
				return i;
		}
		return -1;
	}

	std::unique_ptr<Clothes> create(int type) {
		return std::unique_ptr < Clothes > { m_clothes[type]->clone() };
	}

private:
	std::vector<std::unique_ptr<Clothes>> m_clothes;
};

int Clothes::find(QString name) {
	return ClothesFactory::instance()->find(name);
}

Clothes* Clothes::clone() {
	return new Clothes{ *this };
}