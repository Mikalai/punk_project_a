#define SRC_FILE_NAME __FILE__

#include <QtCore/qjsondocument.h>
#include <QtCore/qjsonarray.h>
#include <QtCore/qjsonobject.h>
#include <QtCore/qjsonvalue.h>
#include <QtCore/qfile.h>
#include <QtCore/qdebug.h>
#include <QtCore/qvector.h>
#include <QOds/Book.hpp>
#include <QOds/Sheet.hpp>
#include <QOds/Row.hpp>
#include <QOds/Cell.hpp>
#include <iostream>
#include "items.h"
#include "string_ex.h"
#include "resources.h"
#include "global_field.h"
#include "model_type.h"
#include "options.h"

Resources::Resources() {
	m_GLOBAL_FIELD_CELL_REAL_SIZE_ground.push_back(std::unique_ptr < QImage > {new QImage{ ":/grass.png" }});
	m_GLOBAL_FIELD_CELL_REAL_SIZE_ground.push_back(std::unique_ptr < QImage > {new QImage{ ":/water.png" }});
	m_GLOBAL_FIELD_CELL_REAL_SIZE_ground.push_back(std::unique_ptr < QImage > {new QImage{ ":/sand.png" }});
	m_GLOBAL_FIELD_CELL_REAL_SIZE_ground.push_back(std::unique_ptr < QImage > {new QImage{ ":/dirt.png" }});
	m_GLOBAL_FIELD_CELL_REAL_SIZE_ground.push_back(std::unique_ptr < QImage > {new QImage{ ":/forest.png" }});
	m_GLOBAL_FIELD_CELL_REAL_SIZE_ground.push_back(std::unique_ptr < QImage > {new QImage{ ":/rocks.png" }});
	m_squad_image.reset(new QImage{ ":/ranger.png" });
	m_city_image.reset(new QImage{ ":/city.png" });

	m_models.resize((int)ModelType::End);
	m_models[(int)ModelType::City].reset(new QImage{ ":/city.png" });
	m_models[(int)ModelType::Squad].reset(new QImage{ ":/ranger.png" });
	m_models[(int)ModelType::Warrior].reset(new QImage{ ":/warrior.png" });
	m_models[(int)ModelType::Worker].reset(new QImage{ ":/worker.png" });
	m_models[(int)ModelType::SawMill].reset(new QImage{ ":/sawmill.png" });
	m_models[(int)ModelType::Construction].reset(new QImage{ ":/construction.png" });

	readItems();
}

std::unique_ptr<Resources> Resources::m_instance;

void Resources::destroy() {
	m_instance.reset(nullptr);
}

Resources* Resources::instance() {
	if (!m_instance.get())
		m_instance.reset(new Resources);
	return m_instance.get();
}

QImage* Resources::getSquadImage() {
	return m_squad_image.get();
}

QImage* Resources::getCityImage() {
	return m_city_image.get();
}

QImage* Resources::modelImage(const ModelType& value) {
	int index = (int)value;
	return m_models.at(index).get();
}

QImage* Resources::loadImage(const QString& value) {
	auto it = m_images.find(value);
	if (it == m_images.end()) {
		auto i = new QImage{ value };
		if (i->isNull()) {
			std::wcout << L"Failed to load " << toWString(value) << std::endl;
		}
		m_images[value].reset(i);
		return i;
	}
	return it->second.get();
}

void Resources::readItems() {
	ods::Book book{ ":/input.ods" };
	if (book.error()) {
		qDebug() << "Failed to open ods book with input data";
		return;
	}

	//
	//	read options
	//
	auto options = book.sheet("Options");
	if (!options) {
		qDebug() << "Options not found";		
	}
	else {
		auto rows = options->rows();
		if (!rows) {
			qDebug() << "No rows for options";
		}
		else {		
			int id_col = -1;
			int name_col = -1;
			int value_col = -1;
			for (int i = 0, max_i = rows->size(); i < max_i; ++i) {				
				auto row = (*rows)[i];
				if (i == 0) {
					auto& cells = row->cells();
					for (int j = 0, max_j = cells.size(); j < max_j; ++j) {
						auto cell = cells[j];

						auto& v = cell->value();
						if (v.IsString()) {
							auto s = v.AsString();
							if (s) {
								if (*s == "id")
									id_col = j;
								else if (*s == "name")
									name_col = j;
								else if (*s == "value")
									value_col = j;
								else 
									qDebug() << "Unexpected option attribute" << *s;
							}
						}
					}
				}
				else {					
					auto id = (int)(*row->cell(id_col)->value().AsDouble());
					auto name = *row->cell(name_col)->value().AsString();
					qDebug() << "Read option" << name;
					if (name == "global_field_width")
						Options::instance()->setOption(OptionType::GlobalFieldWidth, (int)(*row->cell(value_col)->value().AsDouble()));
					else if (name == "global_field_height")
						Options::instance()->setOption(OptionType::GlobalFieldHeight, (int)(*row->cell(value_col)->value().AsDouble()));
					else if (name == "local_field_width")
						Options::instance()->setOption(OptionType::LocalFieldWidth, (int)(*row->cell(value_col)->value().AsDouble()));
					else if (name == "local_field_height")
						Options::instance()->setOption(OptionType::LocalFieldHeight, (int)(*row->cell(value_col)->value().AsDouble()));
					else if (name == "cell_size")
						Options::instance()->setOption(OptionType::CellSize, (int)(*row->cell(value_col)->value().AsDouble()));
					else
						qDebug() << "Unexpected option" << name;
				}
			}
		}
	}

	//	
	//	Read clothes
	//
	auto options = book.sheet("Clothes");
	if (!options) {
		qDebug() << "Clothes not found";
	}
	else {
		auto rows = options->rows();
		if (!rows) {
			qDebug() << "No rows for clothes";
		}
		else {
			int id_col = -1;
			int name_col = -1;
			int description_col = -1;
			int icon_col = -1;
			int weight_col = -1;
			int technology_col = -1;
			int wind_protection_col = -1;
			int water_resistance_col = -1;
			int radiation_resistance_col = -1;
			int heat_absorption_col = -1;
			int target_col = -1;

			for (int i = 0, max_i = rows->size(); i < max_i; ++i) {
				auto row = (*rows)[i];
				if (i == 0) {
					auto& cells = row->cells();
					for (int j = 0, max_j = cells.size(); j < max_j; ++j) {
						auto cell = cells[j];

						auto& v = cell->value();
						if (v.IsString()) {
							auto s = v.AsString();
							if (s) {
								if (*s == "id")
									id_col = j;
								else if (*s == "name")
									name_col = j;
								else if (*s == "description")
									description_col = j;
								else if (*s == "icon")
									icon_col = j;
								else if (*s == "weight")
									weight_col = j;
								else if (*s == "technology")
									technology_col = j;
								else if (*s == "wind_protection")
									wind_protection_col = j;
								else if (*s == "water_resistance")
									water_resistance_col = j;
								else if (*s == "radiation_resistance")
									radiation_resistance_col = j;
								else if (*s == "heat_absorption")
									heat_absorption_col = j;
								else if (*s == "target")
									target_col = j;
								else
									qDebug() << "Unexpected clothes attribute" << *s;
							}
						}
					}
				}
				else {
					auto id = (int)(*row->cell(id_col)->value().AsDouble());
					auto name = *row->cell(name_col)->value().AsString();
					auto description = *row->cell(description_col)->value().AsString();
					auto icon = *row->cell(icon_col)->value().AsString();
					auto weight = *row->cell(weight_col)->value().AsDouble();
					auto technology = (int)(*row->cell(technology_col)->value().AsDouble());
					auto wind_protection = *row->cell(wind_protection_col)->value().AsDouble();
					auto water_resistance = *row->cell(water_resistance_col)->value().AsDouble();
					auto radiation_resistance = *row->cell(radiation_resistance_col)->value().AsDouble();
					auto heat_absorption = *row->cell(heat_absorption_col)->value().AsDouble();
					auto target = fromString(*row->cell(target_col)->value().AsString());
				}
			}
		}
	}


	/*QFile file{ ":/item_classes.json" };
	if (!file.open(QIODevice::ReadOnly)) {
		qCritical() << "Can't read items classes";
		return;
	}

	auto byte_array = file.readAll();

	QJsonDocument doc = QJsonDocument::fromJson(byte_array);

	auto o = doc.object();	

	for (auto& cloth : o["Clothes"].toArray()) {
		auto c = cloth.toObject();
		ClothesClassPtr current{ make_ptr(new ClothesClass{}) };		
		current->setName(c["name"].toString());
		current->setDescription(c["description"].toString());
		current->setIcon(c["icon"].toString());
		current->setWeight(c["weight"].toDouble());
		current->setTechnologyLevel(c["technology"].toInt());
		current->setTargetBodyPart(fromString(c["target"].toString()));									
		current->setWindProtection(c["wind_protection"].toDouble());			
		current->setWaterResistance(c["water_resistance"].toDouble());			
		current->setRadiationResistance(c["radiation_resistance"].toDouble());			
		current->setHeatRadiationAbsorption(c["heat_absorption"].toDouble());
		m_items_cache.push_back(current.get());
		m_clothes_cache.push_back(current.get());
		m_items.push_back(cast<ItemClass>(current));
	}

	for (auto& ammo : o["Ammo"].toArray()) {
		auto a = ammo.toObject();
		AmmoClassPtr current{ make_ptr(new AmmoClass{}) };
		current->setName(a["name"].toString());
		current->setDescription(a["description"].toString());
		current->setIcon(a["icon"].toString());
		current->setWeight(a["weight"].toDouble());
		current->setTechnologyLevel(a["technology"].toInt());
		current->setCaliber(a["caliber"].toDouble());
		current->setCartridge(a["cartridge"].toString());
		current->setEnergy(a["energy"].toDouble());
		current->setSpeed(a["speed"].toDouble());
		current->setManufacture(a["manufacture"].toString());
		m_items_cache.push_back(current.get());
		m_ammo_cache.push_back(current.get());
		m_items.push_back(cast<ItemClass>(current));
	}

	for (auto& weapon : o["Weapon"].toArray()) {
		auto w = weapon.toObject();
		WeaponClassPtr current{ make_ptr(new WeaponClass{}) };
		current->setName(w["name"].toString());
		current->setDescription(w["description"].toString());
		current->setIcon(w["icon"].toString());
		current->setWeight(w["weight"].toDouble());
		current->setTechnologyLevel(w["technology"].toInt());
		current->setCartridge(w["cartridge"].toString());
		current->setWidth(w["width"].toDouble());
		current->setHeight(w["height"].toDouble());
		current->setBarrelLength(w["barrel_length"].toDouble());
		current->setRange(w["range"].toDouble());
		current->setRounds(w["rounds"].toInt());
		m_items_cache.push_back(current.get());
		m_weapon_cache.push_back(current.get());
		m_items.push_back(cast<ItemClass>(current));
	}

	for (auto& surface : o["SurfaceTypes"].toArray()) {
		auto s = surface.toObject();
		SurfaceTypeClassPtr current{ make_ptr(new SurfaceTypeClass{}) };
		current->setName(s["name"].toString());
		current->setIsLand(s["land"].toInt());
		current->setMovePenalty(s["move_penalty"].toDouble());
		current->setIcon(s["icon"].toString());
		m_surfaces_cache.push_back(current.get());
		m_surface_types.push_back(std::move(current));
	}*/
}