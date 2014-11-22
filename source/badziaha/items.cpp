#include <QtCore/qfile.h>
#include <QtCore/qdebug.h>
#include <QtCore/qtextstream.h>
#include "resources.h"
#include <iostream>
#include "items.h"
#include "string_ex.h"
#include "singletone.h"
#include "body_part_type.h"

void destroy_item_class(ItemClass* value) {
	delete value;
}

void destroy_clothes_class(ClothesClass* value) {
	delete value;
}

void destroy_item(Item* value) {
	delete value;
}
void destroy_clothes(Clothes* value) {
	delete value;
}


//class ClothesFactory : public Singletone < ClothesFactory > {
//public:
//	ClothesFactory() {
//		QFile file{ ":/clothes/clothes/config.ini" };
//		QTextStream stream{ &file };
//		if (file.open(QIODevice::ReadOnly)) {
//			ClothesClassPtr current{ make_ptr(new ClothesClass{}) };
//			while (!stream.atEnd()) {
//				auto s = stream.readLine();
//				if (s == "{") {
//					current.reset(new ClothesClass{});
//				}
//				else if (s == "}") {
//					m_clothes.push_back(std::move(current));
//				}
//				else {
//					auto ss = s.split("=");
//					if (ss.size() == 2) {
//						auto name = ss[0].trimmed();
//						auto value = ss[1].trimmed();
//						if (name == "name") {
//							current->setName(value);
//						}
//						else if (name == "target") {
//							current->setTargetBodyPart(fromString(value));
//						}
//						else if (name == "description") {
//							current->setDescription(value);
//						}
//						else if (name == "icon") {
//							current->setIcon(Resources::instance()->loadImage(value));
//						}
//						else if (name == "weight") {
//							current->setWeight(value.toFloat());
//						}
//						else if (name == "technology") {
//							current->setTechnologyLevel(value.toFloat());
//						}
//						else if (name == "wind_protection") {
//							current->m_wind_protection = value.toFloat();
//						}
//						else if (name == "water_resistance"){
//							current->m_water_resistance = value.toFloat();
//						}
//						else if (name == "radiation_resistance") {
//							current->m_radiation_resistance = value.toFloat();
//						}
//						else if (name == "heat_absorption") {
//							current->m_heat_radiation_absorption = value.toFloat();
//						}
//						else {
//							QString s = "Unexpected parameter " + name + " = " + value;
//							auto std_s = toWString(s);
//							std::wcerr << std_s << std::endl;
//						}
//					}
//				}
//			}
//		}
//	}
//
//	int find(QString name) {
//		for (int i = 0, max_i = (int)m_clothes.size(); i < max_i; ++i) {
//			if (m_clothes[i]->name() == name)
//				return i;
//		}
//		qDebug() << "Can't find clothes" << name;
//		return -1;
//	}
//
//	ClothesClassPtr create(int type) {
//		return make_ptr(m_clothes[type]->clone());
//	}
//
//private:
//	std::vector<ClothesClassPtr> m_clothes;
//};

//int ClothesClass::find(QString name) {
//	return ClothesFactory::instance()->find(name);
//}
//
//ClothesClass* ClothesClass::clone() {
//	return new ClothesClass{ *this };
//}
//
//ClothesClassPtr ClothesClass::create(int index) {
//	return ClothesFactory::instance()->create(index);
//}

const QString ItemClass::ToString() const {
	QString v = "<b>" + name() + "</b><br/>";
	v += "<font color='blue'>Weight: </font>" + QString::number(weight()) + "<br/>";
	v += "<font color='blue'>Level: </font>" + QString::number(technologyLevel()) + "<br/>";
	return v;
}

const QString ClothesClass::ToString() const {
	QString v = ItemClass::ToString();
	v += "<font color='red'>Wind protection: </font>" + QString::number(windProtection()) + "<br/>";
	v += "<font color='red'>Heat absorption: </font>" + QString::number(heatRadiationAbsorption()) + "<br/>";
	v += "<font color='red'>Water resistance: </font>" + QString::number(waterResistance()) + "<br/>";
	v += "<br/>" + description();
	return v;
}

ClothesPtr ClothesClass::createInstance() const {
	return make_ptr<Clothes>(new Clothes{ this });
}

void ItemClass::setIcon(QString value) {
	m_icon_name = value;
	m_icon = QImage{ m_icon_name };
	if (m_icon.isNull()) {
		qDebug() << "Failed to load image " << value;
	}
}