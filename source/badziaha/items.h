#ifndef _H_ITEMS
#define _H_ITEMS

#include <QtCore/qstring.h>
#include <QtGui/qimage.h>
#include <set>
#include <memory>
#include "body_part_type.h"
#include "spatial.h"
#include "item_class_type.h"
#include "fwd_items.h"

class Clothes;
class Item;

class ItemClass {
public:

	ItemClass(ItemClassType value) :
		m_type{ value }
	{}

	virtual ~ItemClass() {}

	ItemClassType classType() const { return m_type; }

	QString name() const { return m_name; }
	QString description() const { return m_description; }
	QImage icon() const { return m_icon; }
	const QString iconName() const { return m_icon_name; }	
	float weight() const { return m_weight; }
	float technologyLevel() const { return m_tech_level; }

	virtual const QString ToString() const;
//protected:
	void setName(const QString& value) {
		m_name = value;
	}

	void setDescription(const QString& value) {
		m_description = value;
	}

	void setIcon(QImage value) {
		m_icon = value;
	}

	void setIcon(QString value);

	void setWeight(float value) {
		m_weight = value;
	}

	void setTechnologyLevel(float level) {
		m_tech_level = level;
	}

private:
	ItemClassType m_type{ ItemClassType::Trash };
	QString m_name{ "Some clothes" };
	QString m_description{ "Some cool stuff" };
	float m_weight{ 0.1f };
	//	integral parameter that determines amount of resources and knowledge that were
	//	used to create this item. In some sense this determines base value of the item.
	float m_tech_level{ 1 };
	QString m_icon_name;
	QImage m_icon;
};

class ClothesClass : public ItemClass {
	friend class ClothesFactory;
public:

	using ClothesList = std::vector < ClothesPtr > ;

	ClothesClass()
		: ItemClass{ ItemClassType::ClothesClass }
	{}

	void setTargetBodyPart(BodyPartType value) { m_target_part = value; }
	BodyPartType targetBodyPart() const { return m_target_part; }
	
	float windProtection() const { return m_wind_protection; }
	float waterResistance() const { return m_water_resistance; }
	float radiationResistance() const { return m_radiation_resistance; }
	float heatRadiationAbsorption() const { return m_heat_radiation_absorption; }
	
	ClothesClass* clone();

	const QString ToString() const override;

	void setWindProtection(float value) { m_wind_protection = value; }
	void setWaterResistance(float value) { m_water_resistance = value; }
	void setRadiationResistance(float value) { m_radiation_resistance = value; }
	void setHeatRadiationAbsorption(float value) { m_heat_radiation_absorption = value; }

	ClothesPtr createInstance() const;

private:
	BodyPartType m_target_part{ BodyPartType::Head };
	float m_wind_protection{ 0.1f };
	float m_water_resistance{ 0.1f };
	float m_radiation_resistance{ 0.1f };
	//	can influence on detection by imager
	float m_heat_radiation_absorption{ 0.1f };
};

class AmmoClass : public ItemClass {
public:
	AmmoClass()
		: ItemClass{ ItemClassType::Ammo }
	{}

	const QString manufacture() const { return m_manufacture; }	
	const QString cartridge() const { return m_cartdridge; }	
	float caliber() const { return m_caliber; }	
	float speed() const { return m_speed; }	
	float energy() const { return m_energy; }

	void setManufacture(const QString value) { m_manufacture = value; }
	void setCartridge(const QString value) { m_cartdridge = value; }
	void setCaliber(float value) { m_caliber = value; }
	void setSpeed(float value) { m_speed = value; }
	void setEnergy(float value) { m_energy = value; }

	const QString ToString() const override;
	AmmoPtr createInstance() const;

private:
	QString m_manufacture;
	QString m_cartdridge;
	float m_caliber;
	float m_speed;
	float m_energy;
};

class WeaponClass : public ItemClass {
public:
	WeaponClass()
		: ItemClass{ ItemClassType::Weapon }
	{}

	float length() const { return m_length; }
	float barrelLength() const { return m_barrel_length; }
	float width() const { return m_width; }
	float height() const { return m_height; }
	const QString cartridge() const { return m_cartridge; }
	float range() const { return m_range; }
	int rounds() const { return m_rounds; }

	void setLength(float value) { m_length = value; }
	void setBarrelLength(float value) { m_barrel_length = value; }
	void setWidth(float value) { m_width = value; }
	void setHeight(float value) { m_height = value; }
	void setCartridge(const QString value) { m_cartridge = value; }
	void setRange(float value) { m_range = value; }
	void setRounds(int value) { m_rounds = value; }

	const QString ToString() const override;
	WeaponPtr createInstance() const;

private:
	float m_length{ 0 };
	float m_barrel_length{ 0 };
	float m_width{ 0 };
	float m_height{ 0 };
	QString m_cartridge;
	float m_range{ 0 };
	int m_rounds{ 1 };
};

class Item {
public:
	Item(const ItemClass* item_class)
		: m_class{ item_class }
	{}

	Item(const Item& value);	
	Item& operator = (const Item&) = delete;

	QString name() const { return itemClass()->name(); }
	QString description() const { return itemClass()->description(); }
	QImage icon() const { return itemClass()->icon(); }
	const QString iconName() const { return itemClass()->iconName(); }
	float weight() const { return itemClass()->weight(); }
	float technologyLevel() const { return itemClass()->technologyLevel(); }
	ItemClassType classType() const { return itemClass()->classType(); }
		
	ItemPtr split(int count);
	void merge(ItemPtr& item);
	int quantity() const { return m_count; }
	virtual ItemPtr clone() const;
	void setCount(int value);

	virtual const QString ToString() const;
	virtual bool isEqual(const Item* value) const;

protected:
	virtual const ItemClass* itemClass() const { return m_class; }	
private:
	const ItemClass* m_class{ nullptr };
	//	count is not clonable
	int m_count{ 1 };
};

class ClothesModification {

};

inline bool operator == (const ClothesModification& l, const ClothesModification& r) {
	return false;
}

class Ammo : public Item {
public:
	Ammo(const AmmoClass* ammo_class)
		: Item{ ammo_class }
	{}


	const QString manufacture() const { return itemClass()->manufacture(); }
	const QString cartridge() const { return itemClass()->cartridge(); }
	float caliber() const { return itemClass()->caliber(); }
	float speed() const { return itemClass()->speed(); }
	float energy() const { return itemClass()->energy(); }
	bool isEqual(const Item* value) const override;
	ItemPtr clone() const override;

	const QString ToString() const override;

protected:
	const AmmoClass* itemClass() const override { return static_cast<const AmmoClass*>(Item::itemClass()); }
private:

};

class Clothes : public Item {
public:
	Clothes(const ClothesClass* clothes_class)
		: Item{ clothes_class }
	{}

	Clothes(const Clothes& value); 

	BodyPartType targetBodyPart() const { return itemClass()->targetBodyPart(); }
	float windProtection() const { return itemClass()->windProtection(); }
	float waterResistance() const { return itemClass()->waterResistance(); }
	float radiationResistance() const { return itemClass()->radiationResistance(); }
	float heatRadiationAbsorption() const { return itemClass()->heatRadiationAbsorption(); }
	bool isEqual(const Item* value) const override;
	ItemPtr clone() const override;

	const QString ToString() const override;

protected:
	const ClothesClass* itemClass() const override { return static_cast<const ClothesClass*>(Item::itemClass()); }
private:
	std::set<ClothesModification> m_mods;
};

class WeaponModification {

};

inline bool operator == (const WeaponModification& l, const WeaponModification& r) {
	return false;
}

class Weapon : public Item {
public:
	Weapon(const WeaponClass* weapon_class)
		: Item{ weapon_class }
	{}

	Weapon(const Weapon& value);

	float length() const { return itemClass()->length(); }
	float barrelLength() const { return itemClass()->barrelLength(); }
	float width() const { return itemClass()->weight(); }
	float height() const { return itemClass()->height(); }
	const QString cartridge() const { return itemClass()->cartridge(); }
	float range() const { return itemClass()->range(); }
	int rounds() const { return itemClass()->rounds(); }

	//	Item override
	bool isEqual(const Item* value) const override;
	ItemPtr clone() const override;
	const QString ToString() const override;	

protected:
	const WeaponClass* itemClass() const override { return static_cast<const WeaponClass*>(Item::itemClass()); }

private:
	std::set<WeaponModification> m_mods;
};
#endif	//	_H_ITEMS
