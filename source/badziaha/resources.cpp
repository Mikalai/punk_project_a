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
	{
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
						auto ok = row->cell(id_col)->value().Ok();
						if (ok) {
							auto id = (int)(*row->cell(id_col)->value().AsDouble());
							auto name = *row->cell(name_col)->value().AsString();
							qDebug() << "Read option" << name;
							if (name == "global_field_width")
								Options::set(OptionType::GlobalFieldWidth, (int)(*row->cell(value_col)->value().AsDouble()));
							else if (name == "global_field_height")
								Options::set(OptionType::GlobalFieldHeight, (int)(*row->cell(value_col)->value().AsDouble()));
							else if (name == "local_field_width")
								Options::set(OptionType::LocalFieldWidth, (int)(*row->cell(value_col)->value().AsDouble()));
							else if (name == "local_field_height")
								Options::set(OptionType::LocalFieldHeight, (int)(*row->cell(value_col)->value().AsDouble()));
							else if (name == "cell_size")
								Options::set(OptionType::CellSize, (int)(*row->cell(value_col)->value().AsDouble()));
							else
								qDebug() << "Unexpected option" << name;
						}
					}
				}
			}
		}
	}

	//	
	//	Read clothes
	//
	{
		auto clothes = book.sheet("Clothes");
		if (!clothes) {
			qDebug() << "Clothes not found";
		}
		else {
			auto rows = clothes->rows();
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
						if (row->cell(id_col)->value().Ok()) {
							auto v = row->cell(id_col)->value().AsDouble();
							auto id = (int)(*v);
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

							ClothesClassPtr c = make_ptr(new ClothesClass{});
							c->setName(name);
							c->setDescription(description);
							c->setIcon(icon);
							c->setWeight(weight);
							c->setTechnologyLevel(technology);
							c->setWindProtection(wind_protection);
							c->setWaterResistance(water_resistance);
							c->setRadiationResistance(radiation_resistance);
							c->setHeatRadiationAbsorption(heat_absorption);
							c->setTargetBodyPart(target);
							m_clothes_cache.push_back(c.get());
							m_items.push_back(cast<ItemClass>(c));
						}
					}
				}
			}
		}
	}

	//	
	//	Read surface types
	//
	{
		auto surface_types = book.sheet("SurfaceTypes");
		if (!surface_types) {
			qDebug() << "Surface types not found";
		}
		else {
			auto rows = surface_types->rows();
			if (!rows) {
				qDebug() << "No rows for surface types";
			}
			else {
				int id_col = -1;
				int name_col = -1;	
				int icon_col = -1;
				int move_penalty_col = -1;
				int solid_col = -1;

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
									else if (*s == "icon")
										icon_col = j;
									else if (*s == "move_penalty")
										move_penalty_col = j;
									else if (*s == "solid")
										solid_col = j;
									else
										qDebug() << "Unexpected surface type attribute" << *s;
								}
							}
						}
					}
					else {
						if (row->cell(id_col)->value().Ok()) {
							auto id = (int)(*row->cell(id_col)->value().AsDouble());
							auto name = *row->cell(name_col)->value().AsString();
							auto icon = *row->cell(icon_col)->value().AsString();
							auto move_penalty = *row->cell(move_penalty_col)->value().AsDouble();
							auto solid = (int)(*row->cell(solid_col)->value().AsDouble());
							
							SurfaceTypeClassPtr c = make_ptr(new SurfaceTypeClass{});
							c->setName(name);
							c->setIcon(icon);
							c->setMovePenalty(move_penalty);
							c->setIsLand(solid != 0);
							m_surfaces_cache.push_back(c.get());
							m_surface_types.push_back(std::move(c));
						}
					}
				}
			}
		}
	}
	//	
	//	Read ammo
	//
	{
		auto ammo = book.sheet("Ammo");
		if (!ammo) {
			qDebug() << "Ammo not found";
		}
		else {
			auto rows = ammo->rows();
			if (!rows) {
				qDebug() << "No rows for ammo";
			}
			else {
				int id_col = -1;
				int name_col = -1;
				int description_col = -1;
				int icon_col = -1;
				int weight_col = -1;
				int technology_col = -1;
				int cartridge_col = -1;
				int caliber_col = -1;
				int manufacture_col = -1;
				int speed_col = -1;
				int energy_col = -1;

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
									else if (*s == "cartridge")
										cartridge_col = j;
									else if (*s == "caliber")
										caliber_col = j;
									else if (*s == "manufacture")
										manufacture_col = j;
									else if (*s == "speed")
										speed_col = j;
									else if (*s == "energy")
										energy_col = j;
									else
										qDebug() << "Unexpected ammo attribute" << *s;
								}
							}
						}
					}
					else {
						if (row->cell(id_col)->value().Ok()) {
							auto v = row->cell(id_col)->value().AsDouble();
							auto id = (int)(*v);
							auto name = *row->cell(name_col)->value().AsString();
							auto description = *row->cell(description_col)->value().AsString();
							auto icon = *row->cell(icon_col)->value().AsString();
							auto weight = *row->cell(weight_col)->value().AsDouble();
							auto technology = (int)(*row->cell(technology_col)->value().AsDouble());
							auto cartridge = *row->cell(cartridge_col)->value().AsString();
							auto caliber = *row->cell(caliber_col)->value().AsDouble();
							auto manufacture = *row->cell(manufacture_col)->value().AsString();
							auto speed = *row->cell(speed_col)->value().AsDouble();
							auto energy = *row->cell(energy_col)->value().AsDouble();

							AmmoClassPtr c = make_ptr(new AmmoClass{});
							c->setName(name);
							c->setDescription(description);
							c->setIcon(icon);
							c->setWeight(weight);
							c->setTechnologyLevel(technology);
							c->setCartridge(cartridge);
							c->setCaliber(caliber);
							c->setManufacture(manufacture);
							c->setSpeed(speed);
							c->setEnergy(energy);
							m_ammo_cache.push_back(c.get());
							m_items.push_back(cast<ItemClass>(c));
						}
					}
				}
			}
		}
	}

	//	
	//	Read weapon
	//
	{
		auto weapon = book.sheet("Weapon");
		if (!weapon) {
			qDebug() << "Weapon not found";
		}
		else {
			auto rows = weapon->rows();
			if (!rows) {
				qDebug() << "No weapons for ammo";
			}
			else {
				int id_col = -1;
				int name_col = -1;
				int description_col = -1;
				int icon_col = -1;
				int weight_col = -1;
				int technology_col = -1;
				int length_col = -1;
				int barrel_length_col = -1;
				int width_col = -1;
				int height_col = -1;
				int cartridge_col = -1;
				int range_col = -1;
				int rounds_col = -1;

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
									else if (*s == "length")
										length_col = j;
									else if (*s == "barrel_length")
										barrel_length_col = j;
									else if (*s == "width")
										width_col = j;
									else if (*s == "height")
										height_col = j;
									else if (*s == "cartridge")
										cartridge_col = j;
									else if (*s == "range")
										range_col = j;
									else if (*s == "rounds")
										rounds_col = j;
									else
										qDebug() << "Unexpected ammo attribute" << *s;
								}
							}
						}
					}
					else {
						if (row->cell(id_col)->value().Ok()) {
							auto v = row->cell(id_col)->value().AsDouble();
							auto id = (int)(*v);
							auto name = *row->cell(name_col)->value().AsString();
							auto description = *row->cell(description_col)->value().AsString();
							auto icon = *row->cell(icon_col)->value().AsString();
							auto weight = *row->cell(weight_col)->value().AsDouble();
							auto technology = (int)(*row->cell(technology_col)->value().AsDouble());
							auto cartridge = *row->cell(cartridge_col)->value().AsString();
							auto width = *row->cell(width_col)->value().AsDouble();
							auto barrel_length = *row->cell(barrel_length_col)->value().AsDouble();
							auto length = *row->cell(length_col)->value().AsDouble();
							auto height = *row->cell(height_col)->value().AsDouble();
							auto range = *row->cell(range_col)->value().AsDouble();
							auto rounds = *row->cell(rounds_col)->value().AsDouble();

							WeaponClassPtr c = make_ptr(new WeaponClass{});
							c->setName(name);
							c->setDescription(description);
							c->setIcon(icon);
							c->setWeight(weight);
							c->setTechnologyLevel(technology);
							c->setCartridge(cartridge);
							c->setLength(length);
							c->setBarrelLength(barrel_length);
							c->setWeight(width);
							c->setHeight(height);
							c->setRange(range);
							c->setRounds(rounds);
							m_weapon_cache.push_back(c.get());
							m_items.push_back(cast<ItemClass>(c));
						}
					}
				}
			}
		}
	}
}