﻿#ifndef _H_CHARACTER
#define _H_CHARACTER

#include <array>
#include <stack>
#include <memory>
#include <queue>
#include <functional>
#include <QtCore/qobject.h>
#include <QtCore/qpoint.h>
#include "entity.h"
#include "enum_helper.h"
#include "weather.h"
#include "body_part_type.h"
#include "item_class_type.h"
#include "fwd_items.h"
#include "fwd_character.h"
#include "model_type.h"

enum class Activity {
	Idle,
	Run,
	Sleep,
	Walk,
	Sweem,
	End
};

class ActivityClass {
public:

	ActivityClass();

	float powerConsume(Activity value) { return m_consume_power[enum_index(value)]; }
	
	static ActivityClass* instance();
	static void destroy();

private:
	std::array<float, enum_size<Activity>::Value> m_consume_power;
	static std::unique_ptr<ActivityClass> m_instance;
};

class Body;
class Item;
class UnitModel;
class GlobalField;
class City;
class Squad;
class Character;
struct WeatherStamp;
class Clothes;
class BodyPart;

extern void delete_part(BodyPart* value);

class BodyPart {
public:

	BodyPart(BodyPartType type, Body* owner)
		: m_body{ owner }
		, m_part{ type }
	{}

	~BodyPart();

	float windProtection() const;
	float heatAbsorbingFactor() const;

	BodyPartType type() const { return m_part; }	

	float relativeWeight() const;

	Clothes* clothes() { return m_clothes.get(); }
	void putClothes(ClothesPtr value);
	ClothesPtr dropClothes() { return std::move(m_clothes); }

	void bindItem(ItemPtr value);
	ItemPtr unbindItem();

	Item* item() { return m_taken_item.get(); }
	const Item* item() const { return m_taken_item.get(); }

	Body* body() { return m_body; }
	Character* character();

private:
	BodyPartType m_part{ BodyPartType::LeftFoot };
	ClothesPtr m_clothes{ make_ptr<Clothes>(nullptr) };
	ItemPtr m_taken_item{ make_ptr<Item>(nullptr) };
	Body* m_body{ nullptr };
};

class Body {
public:
	Body(Character* character);
	~Body();

	float windProtection() const;
	float heatAbsorbingFactor() const;
	float temperature() const { return m_temperature; }
	void update(float dt);
	float mass() const;
	float surface() const { return m_surface; }
	float projectedSurface() const { return 0.4f*surface(); }
	float energy() const;

	//	power
	float metabolismConstant() const { return m_metabolism_constant; }
	float metabolismPower() const;
	float radiativePower() const;
	float shortWaveRadiation() const;
	float longWaveRadiation() const;
	float evaporationLost() const;
	float emissivity() const { return m_emissivity; }
	float convectionHeat() const;
	float maxWaterEvaporationPerHour() const { return m_max_evaporation_per_hour; }
	float maxPowerSurplus() const;
	float powerSurplus() const;
	void heatBalance(float dt);
	//	returns amount of liters that should be evaporated to consume power
	float powerToEvaporatedWater(float power);

	std::vector<std::unique_ptr<BodyPart>> parts;	
	
	Character* character() const { return m_character; }

	void die();

	float minTemperature() const { return m_min_temperature; }
	float maxTemperature() const { return m_max_temperature; }
	float water() const { return m_water; }
	float minWater() const { return m_min_water; }
	float maxWater() const { return m_max_water; }

	bool isAlive() const { return m_alive; }

	BodyPart* part(BodyPartType type) {
		return parts[enum_index(type)].get();
	}

	///	Returns a body part that wear specified clothes
	BodyPart* wearClothes(const Clothes* item);

private:
	void satisfyThirst();

private:
	Character* m_character{ nullptr };
	bool m_alive{ true };
	float m_min_temperature{ 15.0f };
	float m_max_temperature{ 43.0f };
	float m_emissivity{ 0.98f };
	float m_metabolism_constant{ 60 };
	float m_fat{ 20 };
	float m_muscle{ 70 };
	float m_temperature{ 36.6f };
	float m_surface{ 1.7f };
	float m_max_evaporation_per_hour{ 1.5 }; //	L / h		
	float m_water{ 4000.0f };
	float m_min_water{ 1000.0f };
	float m_max_water{ 5000.0f };
};

class Hand {
public:
	Hand(BodyPart* part)
		: m_part{ part }
	{}

	bool doHold(ItemClassType type);

	ItemPtr dropItem() {
		if (m_part)
			return m_part->unbindItem();
		return make_ptr<Item>(nullptr);
	}

	void take(ItemPtr value) {
		if (m_part) {
			m_part->bindItem(std::move(value));
		}
	}

	Item* item() {
		if (m_part)
			return m_part->item();
		return nullptr;
	}

private:
	BodyPart* m_part{ nullptr };
};

class Hands {
public:
	Hands(BodyPart* left, BodyPart* right)
		: m_left{ left }
		, m_right{ right }
	{}

	bool doHold(ItemClassType type) {
		if (m_left.doHold(type))
			return true;
		if (m_right.doHold(type))
			return true;
		return false;
	}

	ItemPtr dropItem(ItemClassType type) {
		if (m_left.doHold(type))
			return m_left.dropItem();
		if (m_right.doHold(type))
			return m_right.dropItem();
		return make_ptr<Item>(nullptr);
	}

	void take(ItemPtr item) {
		if (!left().item())
			left().take(std::move(item));
		else if (!right().item())
			right().take(std::move(item));
		else
			left().take(std::move(item));
	}

	Hand& left() { return m_left; }
	Hand& right() { return m_right; }

private:
	Hand m_left;
	Hand m_right;
};

class Character final : public Entity {
	Q_OBJECT;
public:
	Character(GlobalField* field, QGraphicsItem* parent = nullptr);
	virtual ~Character();

	int builderLevel() const { return m_builder_level; }
	int warriorLevel() const { return m_warrior_level; }

	City* city() { return m_current_city; };
	
	QString name() const { return m_name; }
	void setName(QString value) { m_name = value; }


	Squad* squad() { return m_current_squad; }

	Body* body() { return &m_body; }
	const Body* body() const { return &m_body; }

	void update() override;

	Activity activity() const { return m_activity; }

	// field or building
	WeatherStamp* weather() const;
	std::vector<HeatSource> heatSources() const;

	BodyPart* bodyPart(BodyPartType type) { return body()->part(type); }
	Hand leftHand() { return Hand{ bodyPart(BodyPartType::LeftPalm) }; }
	Hand rightHand() { return Hand{ bodyPart(BodyPartType::RightPalm) }; }
	Hands hands() { return Hands{ bodyPart(BodyPartType::LeftPalm), bodyPart(BodyPartType::RightPalm) }; }

	// inventory managment
	bool hasItem(const Item* item) const;
	bool take(ItemPtr item);
	bool canTake(Item* value);
	void takeOrDrop(ItemPtr item);
	bool putOn(const Clothes* item);
	bool putOff(const Clothes* item);
	void drop(ItemPtr item);
	const std::vector<const Item*> selectItems(ItemClassType type) const;	
	const std::vector<const Item*> selectEquippedItems(ItemClassType type) const;
	const std::vector<Item*> selectItems(ItemClassType type);
	const std::vector<Item*> selectEquippedItems(ItemClassType type);
	ItemPtr popItem(const Item* item);
	ItemPtr popOneItem(const Item* item);
	bool takeInHand(const Item* item);

	//	QGraphicsItem
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) override;
	QRectF boundingRect() const override;

	enum { Type = QGraphicsItem::UserType + (int)ModelType::Character};

	int type() const override {
		return Type;
	}

	//	commands
	void injectClip(WeaponClip* clip, Weapon* weapon, std::function<void()> on_complete);
	void ejectClip(Weapon* weapon, std::function<void()> on_complete);
	void loadClip(WeaponClip* clip, Ammo* ammo, std::function<void()> on_complete);
	void unloadClip(WeaponClip* clip, std::function<void()> on_complete);

	//	callbacks
	void setInvetoryChanged(std::function<void()> callback) {
		inventoryChanged = callback;
	}

private:
	void processTasks();
	void setCity(City* value) { m_current_city = value; }
	void setSquad(Squad* value) { m_current_squad = value; }

	friend void joinSquad(Squad* squad, Character* Character);
	friend void leaveSquad(Character* Character);

	friend void enterCity(City* city, Character* Character);
	friend void leaveCity(Character* Character);	

private:
	QString m_name{ "Vitaut" };
	Activity m_activity{ Activity::Idle };
	float m_health{ 10 };
	float m_min_damage{ 1 };
	float m_max_damage{ 2 };
	float m_speed{ 1 };
	bool m_can_shoot_air{ false };
	bool m_can_shoot{ false };
	bool m_can_fly{ false };
	float m_attack_distance{ 1 };
	int m_warrior_level{ 0 };
	int m_builder_level{ 0 };
	City* m_current_city{ nullptr };
	Squad* m_current_squad{ nullptr };
	Body m_body;

	//	task managment
	enum class TaskType {
		Idle,
		InjectClip,
		EjectClip = InjectClip,
		LoadClip, 
		UnloadClip = LoadClip,
		Eat,
		Drink,		
	};

	class Task {
	public:
		Task(TaskType type, float time, std::function<void()> on_complete)
			: m_time_to_complete{ time }
			, m_on_complete{ on_complete }
			, m_type{ type }
		{}

		virtual ~Task() {};

		virtual bool update(float dt) {
			if (m_time_to_complete < 0)
				return false;
			m_time_to_complete -= dt;
			if (m_time_to_complete <= 0) {
				m_on_complete();
				return true;
			}
			return false;
		}

		float timeLeft() const { return m_time_to_complete; }
		TaskType type() const { return m_type; }

	private:
		TaskType m_type{ TaskType::Idle };
		float m_time_to_complete{ -1 };
		std::function<void()> m_on_complete;
	};

	std::queue<Task> m_tasks;

	//	inventory
	std::vector<ItemPtr> m_items;

	friend bool operator < (const Character::Task& a, const Character::Task& b);

	//	callbacks
	std::function<void()> inventoryChanged;
};

inline bool operator < (const Character::Task& a, const Character::Task& b) {
	return a.type() < b.type();
}

#endif	//_H_Character