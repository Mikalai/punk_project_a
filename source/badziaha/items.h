#ifndef _H_ITEMS
#define _H_ITEMS

#include <QtCore/qstring.h>
#include <QtGui/qimage.h>
#include <memory>
#include "body_part_type.h"
#include "spatial.h"
#include "item_class_type.h"
#include "fwd_items.h"

class Item {
public:

	Item(ItemClassType value) :
		m_type{ value }
	{}

	virtual ~Item() {}

	ItemClassType classType() const { return m_type; }

	QString name() const { return m_name; }
	QString description() const { return m_description; }

	QImage* icon() const { return m_icon; }
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

	void setIcon(QImage* value) {
		m_icon = value;
	}

	void setIcon(QString value) {
		m_icon_name = value;
	}

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
	QImage* m_icon{ nullptr };
};

class ClothesFactory;

class Clothes : public Item {
	friend class ClothesFactory;
public:

	Clothes()
		: Item{ ItemClassType::Clothes }
	{}

	void setTargetBodyPart(BodyPartType value) { m_target_part = value; }
	BodyPartType targetBodyPart() const { return m_target_part; }
	
	float windProtection() const { return m_wind_protection; }
	float waterResistance() const { return m_water_resistance; }
	float radiationResistance() const { return m_radiation_resistance; }
	float heatRadiationAbsorption() const { return m_heat_radiation_absorption; }
	
	static int find(QString name);
	static ClothesPtr create(int type);

	Clothes* clone();

	const QString ToString() const override;

	void setWindProtection(float value) { m_wind_protection = value; }
	void setWaterResistance(float value) { m_water_resistance = value; }
	void setRadiationResistance(float value) { m_radiation_resistance = value; }
	void setHeatRadiationAbsorption(float value) { m_heat_radiation_absorption = value; }

private:
	BodyPartType m_target_part{ BodyPartType::Head };
	float m_wind_protection{ 0.1f };
	float m_water_resistance{ 0.1f };
	float m_radiation_resistance{ 0.1f };
	//	can influence on detection by imager
	float m_heat_radiation_absorption{ 0.1f };
};

#endif	//	_H_ITEMS