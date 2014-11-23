#include <QtCore/qjsondocument.h>
#include <QtCore/qjsonarray.h>
#include <QtCore/qjsonobject.h>
#include <QtCore/qjsonvalue.h>
#include <QtCore/qfile.h>
#include <QtCore/qdebug.h>
#include <iostream>
#include "items.h"
#include "string_ex.h"
#include "resources.h"
#include "global_field.h"
#include "model_type.h"

Resources::Resources() {
	m_global_field_cell_ground.push_back(std::unique_ptr < QImage > {new QImage{ ":/grass.png" }});
	m_global_field_cell_ground.push_back(std::unique_ptr < QImage > {new QImage{ ":/water.png" }});
	m_global_field_cell_ground.push_back(std::unique_ptr < QImage > {new QImage{ ":/sand.png" }});
	m_global_field_cell_ground.push_back(std::unique_ptr < QImage > {new QImage{ ":/dirt.png" }});
	m_global_field_cell_ground.push_back(std::unique_ptr < QImage > {new QImage{ ":/forest.png" }});
	m_global_field_cell_ground.push_back(std::unique_ptr < QImage > {new QImage{ ":/rocks.png" }});
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

QImage* Resources::getImage(const SurfaceType& value) {
	return m_global_field_cell_ground.at((int)value).get();
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
	QFile file{ ":/item_classes.json" };
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
}