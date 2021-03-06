#include <QtCore/qfile.h>
#include <QtCore/qdebug.h>
#include <QtCore/qtextstream.h>
#include "resources.h"
#include <iostream>
#include "items.h"
#include "string_ex.h"
#include "singletone.h"
#include "body_part_type.h"

void destroy(ItemClass* value) {
	delete value;
}

void destroy(ClothesClass* value) {
	delete value;
}

void destroy(AmmoClass* value) {
	delete value;
}

void destroy(Item* value) {
	delete value;
}

void destroy(Clothes* value) {
	delete value;
}

void destroy(Ammo* value) {
	delete value;
}

void destroy(WeaponClass* value) {
	delete value;
}

void destroy(Weapon* value) {
	delete value;
}

void destroy(WeaponClipClass* value) {
	delete value;
}

void destroy(WeaponClip* value) {
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

const QString Item::ToString() const {
	QString v = "<b>" + name() + "</b><br/>";
	v += "<font color='blue'>Weight: </font>" + QString::number(weight()) + " (" + QString::number(weight()*quantity()) + ") kg <br/>";
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

const QString Clothes::ToString() const {
	QString v = Item::ToString();
	v += "<font color='red'>Wind protection: </font>" + QString::number(windProtection()) + "<br/>";
	v += "<font color='red'>Heat absorption: </font>" + QString::number(heatRadiationAbsorption()) + "<br/>";
	v += "<font color='red'>Water resistance: </font>" + QString::number(waterResistance()) + "<br/>";
	v += "<br/>" + description();
	return v;
}

const QString AmmoClass::ToString() const {
	QString v = ItemClass::ToString();
	v += "<font color='red'>Cartridge: </font>" + cartridge() + "<br/>";
	v += "<font color='red'>Manufacture: </font>" + manufacture() + "<br/>";
	v += "<font color='red'>Caliber: </font>" + QString::number(caliber()) + " mm<br/>";
	v += "<font color='red'>Seed: </font>" + QString::number(speed()) + " m/s<br/>";
	v += "<font color='red'>Energy: </font>" + QString::number(energy()) + " J<br/>";
	v += "<br/>" + description();
	return v;
}

const QString WeaponClass::ToString() const {
	QString v = ItemClass::ToString();
	v += "<font color='red'>Cartridge: </font>" + cartridge() + "<br/>";
	v += "<font color='red'>Range: </font>" + QString::number(range()) + " m<br/>";
//	v += "<font color='red'>Rounds: </font>" + QString::number(rounds()) + "<br/>";
	v += "<br/>" + description();
	return v;
}

const QString WeaponClipClass::ToString() const {
	QString v = ItemClass::ToString();
	v += "<font color='red'>Weapon: </font>" + weapon() + "<br/>";
	v += "<font color='red'>Rounds: </font>" + QString::number(rounds()) + "<br/>";
	v += "<br/>" + description();
	return v;
}

const QString Ammo::ToString() const {
	QString v = Item::ToString();
	v += "<font color='red'>Cartridge: </font>" + cartridge() + "<br/>";
	v += "<font color='red'>Manufacture: </font>" + manufacture() + "<br/>";
	v += "<font color='red'>Caliber: </font>" + QString::number(caliber()) + " mm<br/>";
	v += "<font color='red'>Seed: </font>" + QString::number(speed()) + " m/s<br/>";
	v += "<font color='red'>Energy: </font>" + QString::number(energy()) + " J<br/>";
	v += "<br/>" + description();
	return v;
}

const QString Weapon::ToString() const {
	QString v = Item::ToString();
	v += "<font color='red'>Cartridge: </font>" + cartridge() + "<br/>";
	v += "<font color='red'>Range: </font>" + QString::number(range()) + " m<br/>";	
	v += "<font color='red'>Clip: </font>" + (clip() ? clip()->name() : "No") + "<br/>";
	if (clip()) {
		v += "<font color='red'>Rounds: </font>" + QString::number(clip()->rounds()) + "/" + QString::number(clip()->maxRounds()) + "<br/>";
	}
	v += "<br/>" + description();
	return v;
}

const QString WeaponClip::ToString() const {
	QString v = Item::ToString();
	v += "<font color='red'>Weapon: </font>" + weapon() + "<br/>";
	v += "<font color='red'>Rounds: </font>" + QString::number(rounds()) + "/" + QString::number(maxRounds()) + "<br/>";
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

bool Item::isEqual(const Item* value) const {
	if (value == nullptr)
		return false;
	if (value->itemClass() != itemClass())
		return false;
	return true;
}

ItemPtr Item::split(int count) {
	if (m_count <= 0) {
		qDebug() << "Can't split" << name() << "with count" << count;
		return make_ptr<Item>(nullptr);
	}
	if (m_count <= count) {
		qDebug() << "Can't split" << name() << "with count" << count;
		return make_ptr<Item>(nullptr);
	}
	auto result = clone();
	result->setCount(count);
	m_count -= count;

	//	any nested classes can split some other parts
	childSplit(result, count);

	qDebug() << name() << "has been splitted with" << count;
	return result;
}

void Item::merge(ItemPtr& item) {
	//	check if merged items are compatible
	if (!isEqual(item.get()))
		return;
	//	increase count
	m_count += item->quantity();
	//	allow complex objects to merge internals
	childMerge(item);
	//	destroy useless item
	item.reset();
}

Item::Item(const Item& value) {
	m_class = value.m_class;
	m_count = 1;	//	count is not copied
}

void Item::setCount(int value) {
	if (value <= 0) {
		qDebug() << "Items count can't be non positive";
		return;
	}
	m_count = value;
}

ItemPtr Item::clone() const {
	return make_ptr(new Item{ *this });
}

Clothes::Clothes(const Clothes& value) 
	: Item{ value } {
	m_mods = value.m_mods;
}

bool Clothes::isEqual(const Item* value) const {
	if (!Item::isEqual(value))
		return false;
	const Clothes* clothes = static_cast<const Clothes*>(value);
	if (m_mods != clothes->m_mods)
		return false;
	return true;
}

ItemPtr Clothes::clone() const {
	ClothesPtr result = make_ptr(new Clothes{ *this });
	return cast<Item>(std::move(result));
}

bool Ammo::isEqual(const Item* value) const {
	if (!Item::isEqual(value))
		return false;
	return true;
}

ItemPtr Ammo::clone() const {
	auto result = make_ptr(new Ammo{ *this });
	return cast<Item>(std::move(result));
}

AmmoPtr AmmoClass::createInstance() const {
	return make_ptr(new Ammo{ this });
}

bool Weapon::isEqual(const Item* value) const {
	if (!Item::isEqual(value))
		return false;
	const Weapon* weapon = static_cast<const Weapon*>(value);
	if (m_mods != weapon->m_mods)
		return false;
	if (clip() && weapon->clip()) {
		if (!clip()->isEqual(weapon->clip()))
			return false;
	}
	if (!clip() && weapon->clip())
		return false;
	if (clip() && !weapon->clip())
		return false;		
	return true;
}

Weapon::Weapon(const Weapon& value) 
	: Item{ value } {
	m_mods = value.m_mods;
	if (value.clip()) {
		m_clip = std::move(cast<WeaponClip>(value.clip()->clone()));		
	}
}

ItemPtr Weapon::clone() const {
	auto result = make_ptr(new Weapon{ *this });
	return cast<Item>(result);
}

void Weapon::childMerge(ItemPtr& value) {		
}

void Weapon::childSplit(ItemPtr& new_parent, int count) {	
}

WeaponPtr WeaponClass::createInstance() const {
	return make_ptr(new Weapon{ this });
}


bool WeaponClip::isEqual(const Item* value) const {
	if (!Item::isEqual(value))
		return false;
	const WeaponClip* clip = static_cast<const WeaponClip*>(value);
	if (m_ammo.get() && clip->m_ammo.get()) {
		if (!m_ammo->isEqual(clip->m_ammo.get()))
			return false;
		if (m_ammo->quantity() != clip->ammo()->quantity())
			return false;
	}
	if (!ammo() && clip->ammo())
		return false;
	if (ammo() && !clip->ammo())
		return false;
	return true;
}

WeaponClip::WeaponClip(const WeaponClip& value)
	: Item{ value } {
	if (value.m_ammo.get()) {
		m_ammo = cast<Ammo>(value.m_ammo->clone());
		m_ammo->setCount(value.m_ammo->quantity());
	}
}

ItemPtr WeaponClip::clone() const {
	auto result = make_ptr(new WeaponClip{ *this });
	return cast<Item>(result);
}

WeaponClipPtr WeaponClipClass::createInstance() const {
	return make_ptr(new WeaponClip{ this });
}

void Weapon::injectClip(WeaponClipPtr value) { 
	m_clip = std::move(value); 
	if (clip()) {
		qDebug() << clip()->name() << "has been injected into" << name();
	}
	else {
		qDebug() << "Bad clip injected into" << name();
	}
}
WeaponClipPtr Weapon::ejectClip() { 
	if (clip()) {
		qDebug() << clip()->name() << "ejected from" << name();
	}
	else {
		qDebug() << "Bad clip ejected from" << name();
	}
	return std::move(m_clip); 
}

const WeaponClass* WeaponClipClass::weaponClass() const {
	if (!m_weapon_class_ptr) {
		auto& weapons = Resources::weapons();
		for (auto& weapon : weapons) {
			if (weapon->name() == m_weapon_class) {
				return m_weapon_class_ptr = weapon;
			}
		}
	}
	return m_weapon_class_ptr;	
}

bool WeaponClip::isAmmoCompatible(Ammo* value) const {
	return value->cartridge() == weaponClass()->cartridge();
}

void WeaponClip::load(AmmoPtr value) {
	if (ammo()) {
		qDebug() << "Loading" << name() << "when it is not empty";
	}
	m_ammo = std::move(value);
}

AmmoPtr WeaponClip::unload() {
	if (!ammo()) {
		qDebug() << "Unloading empty clip" << name(); 
	}
	return std::move(m_ammo);
}