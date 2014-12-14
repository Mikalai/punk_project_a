
#include <QtGui/qpainter.h>
#include <QtCore/qdebug.h>
#include "weather.h"
#include "global_field.h"
#include "constants.h"
#include "Character.h"
#include "items.h"
#include "unit_graphics_item.h"
#include "known_stuff.h"

void destroy(Character* value) {
	delete value;
}

bool Hand::doHold(ItemClassType type) {
	return m_part && m_part->item() && m_part->item()->classType() == type;
}

std::unique_ptr<ActivityClass> ActivityClass::m_instance;

ActivityClass* ActivityClass::instance() {
	if (!m_instance.get())
		m_instance.reset(new ActivityClass);
	return m_instance.get();
}

void ActivityClass::destroy() {
	m_instance.reset(nullptr);
}

ActivityClass::ActivityClass() {
	m_consume_power[enum_index(Activity::Idle)] = 60;
	m_consume_power[enum_index(Activity::Run)] = 810;
	m_consume_power[enum_index(Activity::Sleep)] = 70;
	m_consume_power[enum_index(Activity::Walk)] = 325;
	m_consume_power[enum_index(Activity::Sweem)] = 670;
}

Character::Character(GlobalField* field, QGraphicsItem* parent)
	: Entity{field, parent }
	, m_body{ this }
{
	auto& clothes_classes = Resources::clothes();
	for (const auto& clothes_class : clothes_classes) {
		auto item = clothes_class->createInstance();
		take(cast<Item>(std::move(item)));
	}
	auto& ammo_classes = Resources::ammos();
	for (const auto& ammo_class : ammo_classes) {
		auto item = ammo_class->createInstance();
		item->setCount(40);
		take(cast<Item>(std::move(item)));
	}
	auto& weapon_classes = Resources::weapons();
	for (auto& weapon_class : weapon_classes) {
		auto item = weapon_class->createInstance();
		item->setCount(2);
		take(cast<Item>(std::move(item)));
	}
	auto& weapon_clip_classes = Resources::weapon_clips();
	for (auto& clip_class : weapon_clip_classes) {
		auto item = clip_class->createInstance();		
		item->setCount(2);
		take(cast<Item>(std::move(item)));
	}
}

void Character::update() {
	Entity::update();
	auto dt = getTimeStep();

	m_body.update(dt);

	processTasks();
}

void Character::processTasks() {
	if (m_tasks.empty())
		return;
	auto& task = m_tasks.front();	
	if (task.update(getTimeStep())) {
		m_tasks.pop();
	}
}

Body::Body(Character* character)
	: m_character{ character } {
	parts.resize(enum_size<BodyPartType>::Value);
	int index = 0;
	for (auto& v : parts) {
		v.reset(new BodyPart{enum_value<BodyPartType>(index), this });
		++index;
	}
}

void BodyPart::bindItem(ItemPtr value) {
	if (m_taken_item.get()) {
		character()->takeOrDrop(std::move(m_taken_item));
	}
	m_taken_item = std::move(value);
}

ItemPtr BodyPart::unbindItem() {
	return std::move(m_taken_item);
}

Character* BodyPart::character() { 
	return body()->character(); 
}

float Body::metabolismPower() const {
	auto A = ActivityClass::instance()->powerConsume(character()->activity());
	auto S = surface();
	auto C = metabolismConstant();
	auto M = A + S*C;
	return M;
}

float Body::windProtection() const {
	float result = 0;
	for (auto& p : parts) {
		auto k = p->relativeWeight();
		auto v = p->windProtection();
		result += k * v;
	}
	return result;
}

float Body::radiativePower() const {
	auto Rl = longWaveRadiation();
	auto Rs = shortWaveRadiation();
	auto R = Rl + Rs;
	return R;
}

float Body::longWaveRadiation() const {
	auto S = surface();
	auto e = emissivity();
	auto sigma = Const::StefanBoltzman;
	auto tskin = temperature() + Const::CelsiusZero;
	tskin = powf(tskin, 4);
	auto tenv = character()->weather()->temperature + Const::CelsiusZero;
	tenv = powf(tenv, 4);
	auto Rl = S * e * sigma * (tskin - tenv);
	return Rl;
}

float Body::shortWaveRadiation() const {
	auto r = heatAbsorbingFactor();
	auto heat_sources = character()->heatSources();
	auto R = 0.0f;
	for (auto& s : heat_sources) {
		R += r * projectedSurface() * s.power(character()->weather(), character()->scenePos());
	}
	return R;
}

float Body::convectionHeat() const {
	auto S = surface();
	auto p = windProtection();
	auto kc = character()->weather()->heatConvectionFactor();
	auto tskin = temperature() + Const::CelsiusZero;
	auto tenv = character()->weather()->temperature + Const::CelsiusZero;
	auto C = S * p * kc * (tskin - tenv);
	return C;
}

float Body::maxPowerSurplus() const {
	auto P = maxWaterEvaporationPerHour() * Const::WaterSpecificHeatVaporization / 3600.0f;
	return P;
}

float Body::powerSurplus() const {
	auto M = metabolismPower();
	auto R = radiativePower();
	auto C = convectionHeat();
	auto P = M + R - C;
	return P;
}

void Body::heatBalance(float dt) {
	auto power_surplus = powerSurplus();
	auto max_power_surplus = maxPowerSurplus();	
	if (power_surplus >= 0 && power_surplus <= max_power_surplus) {
		// compensate power surplus through water evaporation
		auto water = powerToEvaporatedWater(power_surplus)*dt;
		m_water -= water;
		if (m_water < 0) {
			die();
			return;
		}
	}
	else if (power_surplus < 0) {
		//	compensate power shortage through body temperature body decrease
		auto Q = power_surplus * dt;
		auto t2 = (Q + Const::HumanBodySpecificHeat * mass() * temperature()) / (mass()*Const::HumanBodySpecificHeat);
		m_temperature = t2;
		if (temperature() < minTemperature()) {
			die();
			return;
		}
	}
	else {
		//	compsate power surplus through body temperature increase
		auto water = powerToEvaporatedWater(maxPowerSurplus())*dt;
		m_water -= water;
		if (m_water < 0) {
			die();
			return;
		}
		power_surplus -= maxPowerSurplus();
		auto Q = power_surplus * dt;
		auto t2 = (Q + Const::HumanBodySpecificHeat * mass() * temperature()) / (mass()*Const::HumanBodySpecificHeat);
		m_temperature = t2;
		if (temperature() > maxTemperature()) {
			die();
			return;
		}
	}
}

void Body::update(float dt) {
	if (!isAlive())
		return;

	heatBalance(dt);
	satisfyThirst();
}

void Body::satisfyThirst() {
	if (water() < minWater()) {
		//character()->
	}
}


//Character* Character::create(GlobalField* field, CharacterType type, QObject* parent) {
//	auto u = new Character{field, parent };
//	if (type == CharacterType::Worker) {
//		qDebug("Worker create...");
//		u->m_builder_level = 1;
//		u->setModel(new CharacterGraphicsItem<Character, ModelType::Worker>(u, nullptr));
//	}
//	else if (type == CharacterType::Warrior) {
//		qDebug("Warrior create...");
//		u->m_warrior_level = 1;
//		u->setModel(new CharacterGraphicsItem<Character, ModelType::Warrior>(u, nullptr));
//	}
//	return u;
//}

std::vector<HeatSource> Character::heatSources() const {
	std::vector<HeatSource> res;
	//if (building()) {
	//	//return building()->heatSources(fullPosition());
	//}
	//else if (field()) {
		res.push_back(HeatSource{});
	//}
	return res;
}

float BodyPart::relativeWeight() const {
	static const float w[] = { 0.0920575f, 0.0920575f, 0.1841149f, 0.1841149f, 0.2761724f, 0.2761724f, 0.0920575f, 0.1742014f, 0.1959766f, 0.2177518f, 0.2395270f, 0.2613021f, 0.2830773f, 0.3048525f, 0.3266277f, 0.3484028f, 0.3701780f, 0.3919532f };
	return w[enum_index(m_part)];
}

void BodyPart::putClothes(ClothesPtr clothes) {
	if (m_clothes.get()) {
		qCritical() << "Body part already has a clothes put on";
	}
	m_clothes = std::move(clothes);
}

BodyPart::~BodyPart() {
	m_clothes.reset();
}

Body::~Body() {
	parts.clear();
}

Character::~Character() {

}

float BodyPart::windProtection() const {
	if (m_clothes) {
		return m_clothes->windProtection();
	}
	return 0;
}

float BodyPart::heatAbsorbingFactor() const {
	if (m_clothes) {
		return m_clothes->heatRadiationAbsorption();
	}
	return 0;
}

float Body::heatAbsorbingFactor() const {
	auto result = 0.0f;
	for (auto& p : parts) {
		auto w = p->relativeWeight();
		auto v = p->heatAbsorbingFactor();
		result += v * w;
	}
	return result;
}

float Body::mass() const {
	return m_muscle + m_fat + m_water;
}

float Body::powerToEvaporatedWater(float power) {
	auto result = power / Const::WaterSpecificHeatVaporization;	//	liter per second
	return result;
}

void Body::die() {
	m_alive = false;
}

WeatherStamp* Character::weather() const {
	return field()->weather();
}

bool Character::take(ItemPtr value) {
	if (!value.get()) {
		qDebug() << name() << "can't take nullptr item";
		return false;
	}	
	//	try to merge item with items in inventory
	auto items = selectItems(value->classType());
	for (auto& item : items) {
		item->merge(value);
		if (!value.get()) {
			qDebug() << item->name() << "has been merged";
			break;
		}
	}

	//	if not merged add new item
	if (value.get()) {
		qDebug() << value->quantity() << "of" << value->name() << "has been taken by" << name();
		m_items.push_back(std::move(value));
	}

	return true;
}

const std::vector<const Item*> Character::selectItems(ItemClassType type) const {
	std::vector<const Item*> res;
	for (auto& item : m_items) {
		if (item->classType() == type) {
			res.push_back(item.get());
		}
	}
	return res;
}

const std::vector<const Item*> Character::selectEquippedItems(ItemClassType type) const {
	std::vector<const Item*> res;
	for (auto& p : body()->parts) {
		if (p->clothes() && type == ItemClassType::ClothesClass)
			res.push_back(p->clothes());
	}
	return res;
}

const std::vector<Item*> Character::selectItems(ItemClassType type) {
	std::vector<Item*> res;
	for (auto& item : m_items) {
		if (item->classType() == type) {
			res.push_back(item.get());
		}
	}
	return res;
}

const std::vector<Item*> Character::selectEquippedItems(ItemClassType type) {
	std::vector<Item*> res;
	for (auto& p : body()->parts) {
		if (p->clothes() && type == ItemClassType::ClothesClass)
			res.push_back(p->clothes());
	}
	return res;
}

ItemPtr Character::popItem(const Item* item) {
	auto it = std::find_if(m_items.begin(), m_items.end(), [&item](const ItemPtr& value) {
		return value.get() == item; 
	});
	if (it == m_items.end())
		return make_ptr<Item>(nullptr);
	auto result = std::move(*it);
	m_items.erase(it);
	return result;
}

ItemPtr Character::popOneItem(const Item* item) {
	auto it = std::find_if(m_items.begin(), m_items.end(), [&item](const ItemPtr& value) {
		return value.get() == item;
	});
	if (it == m_items.end())
		return make_ptr<Item>(nullptr);
	if (item->quantity() == 1) {
		auto result = std::move(*it);
		m_items.erase(it);
		return result;
	}
	else {
		return (*it)->split(1);
	}
}

bool Character::putOn(const Clothes* clothes) {
	
	auto item = popItem(clothes);
	if (!item.get())
		return false;

	//	insure item can be put on on some body part
	auto part = body()->part(clothes->targetBodyPart());
	if (!part) {
		qDebug() << "Can't put" << clothes->name() << ". Body has got no part" << clothes->targetBodyPart();
		return false;
	}

	//	put off any already put on clothes on this body part
	if (part->clothes()) {
		m_items.push_back(cast<Item>(part->dropClothes()));
	}

	part->putClothes(make_ptr(static_cast<Clothes*>(item.release())));
	qDebug() << clothes->name() << "has been put on " << toString(part->type());
	return true;
}

bool Character::putOff(const Clothes* item) {
	if (!item) {
		qDebug() << "Can't put off nullptr";
		return false;
	}

	auto part = body()->wearClothes(item);
	if (part == nullptr)
		return false;
	
	qDebug() << item->name() << "has been put off from " << toString(part->type());
	m_items.push_back(cast<Item>(part->dropClothes()));
	return true;
}

BodyPart* Body::wearClothes(const Clothes* item) {
	auto it = std::find_if(parts.begin(), parts.end(), [&item](std::unique_ptr<BodyPart>& part) {
		return part->clothes() == item; });
	if (it == parts.end())
		return nullptr;
	return (*it).get();
}

void Character::drop(ItemPtr item) {	
	if (!item.get()) {
		qDebug() << "Can't drop" << item->name() << ". Not in inventory";
	}
	qDebug() << item->name() << "has been dropped";
	field()->addItemInstance(scenePos(), std::move(item));	
}

void Character::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
	auto body = Resources::instance()->loadImage(":/body/body_male.png");
	auto head = Resources::instance()->loadImage(":/body/head_male.png");

	auto brush = painter->brush();
	brush.setStyle(Qt::BrushStyle::SolidPattern);
	brush.setColor(QColor(255, 0, 0));
	brush.setTextureImage(*body);		
	painter->setBrush(brush);	
	//painter->fillRect(boundingRect(), brush);
	painter->drawImage(boundingRect().bottomLeft(), *body, boundingRect());

	brush = painter->brush();
	brush.setStyle(Qt::BrushStyle::SolidPattern);
	brush.setColor(QColor(255, 0, 0));
	brush.setTextureImage(*head);		
	painter->setBrush(brush);
	//painter->fillRect(boundingRect(), brush);
	painter->drawPixmap(boundingRect(), QPixmap::fromImage(*body), QRectF(0, 0, body->width(), body->height()));
	painter->drawPixmap(QRectF(-10, -10, 20, 20), QPixmap::fromImage(*head), QRectF( 0, 0, head->width(), head->height() ));

	//Entity::paint(painter, option, widget);
}

QRectF Character::boundingRect() const {
	return Entity::boundingRect();
}

void Character::injectClip(WeaponClip* clip, Weapon* weapon, std::function<void()> on_complete) {
	m_tasks.push(Task{ TaskType::InjectClip, 0, [clip, weapon, this]() {
		if (!hasItem(clip))
			return;
		if (!hasItem(weapon))
			return;
		hands().take(popOneItem(clip));
		hands().take(popOneItem(weapon));
		inventoryChanged();

		m_tasks.push(Task{ TaskType::InjectClip, 2, [clip, weapon, this]() {
			if (weapon->clip()) {
				auto old_clip = weapon->ejectClip();
				take(cast<Item>(old_clip));
			}
			//	take one clip from inventory
			auto clip_item = cast<WeaponClip>(hands().dropItem(ItemClassType::WeaponClip));
			//	take one weapon from inventory
			auto weapon_item = cast<Weapon>(hands().dropItem(ItemClassType::Weapon));
			//	inject clip into the weapon
			weapon_item->injectClip(std::move(clip_item));
			//	put weapon into the inventory
			take(cast<Item>(weapon_item));
			//	call on complete
			inventoryChanged();
		} });
	} });
}

void Character::ejectClip(Weapon* weapon, std::function<void()> on_complete) {
	m_tasks.push( Task{ TaskType::EjectClip, 0, [weapon, this]() {
		if (!hasItem(weapon))
			return;
		hands().take(popOneItem(weapon));
		inventoryChanged();
		
		m_tasks.push(Task{ TaskType::EjectClip, 2, [weapon, this]() {
			//	take one weapon
			WeaponPtr weapon_item = cast<Weapon>(hands().dropItem(ItemClassType::Weapon));
			//	eject clip from weapon
			auto clip_item = weapon_item->ejectClip();
			//	put clip in the inventory
			take(cast<Item>(clip_item));
			//	put gun back in the inventory
			take(cast<Item>(weapon_item));
			//	call on complete
			inventoryChanged();
		} });
	} });
}

void Character::loadClip(WeaponClip* clip, Ammo* ammo, std::function<void()> on_complete) {
	m_tasks.push(Task{ TaskType::LoadClip, 0, [clip, ammo, this]() {
		if (!hasItem(clip))
			return;
		if (!hasItem(ammo))
			return;
		hands().take(popOneItem(clip));
		//	get clip capacity
		auto capacity = clip->maxRounds();
		//	take all ammo
		auto ammo_item = cast<Ammo>(popItem(ammo));
		if (capacity >= ammo_item->quantity()) {
			//	take ammo in the hands
			hands().take(cast<Item>(ammo_item));
		}
		else {
			//	split ammo
			auto splitted_ammo = cast<Ammo>(ammo_item->split(capacity));
			//	take ammo in the hands
			hands().take(cast<Item>(splitted_ammo));
			//	put the rest back into the inventory
			take(cast<Item>(ammo_item));
		}

		inventoryChanged();

		//	when took all in hands create a task
		m_tasks.push(Task{ TaskType::LoadClip, 2, [clip, ammo, this](){
			//	take one clip
			auto clip_item = cast<WeaponClip>(hands().dropItem(ItemClassType::WeaponClip));
			//	take new ammo
			auto ammo_item = cast<Ammo>(hands().dropItem(ItemClassType::Ammo));
			//	unload loaded ammo
			auto old_ammo = clip_item->unload();
			if (old_ammo.get()) {
				take(cast<Item>(old_ammo));
			}
			//	load ammo
			clip_item->load(std::move(ammo_item));
			//	put clip back into inventory
			take(cast<Item>(clip_item));
			//	call callback
			inventoryChanged();
		} });
	} });
}

void Character::unloadClip(WeaponClip* clip, std::function<void()> on_complete) {

}

void Character::takeOrDrop(ItemPtr value) {
	if (!canTake(value.get())) {
		drop(std::move(value));
	}
	take(std::move(value));
	inventoryChanged();
}

bool Character::takeInHand(const Item* value) {
	auto item = popOneItem(value);
	if (!item.get()) {
		qDebug() << "Can't take item" << value->name() << ". Not found in inventory";
		return false;
	}

	hands().take(std::move(item));

	inventoryChanged();

	return true;
}

bool Character::canTake(Item* value) {
	return true;
}

bool Character::hasItem(const Item* item) const {
	auto it = std::find_if(m_items.begin(), m_items.end(), [item](const ItemPtr& value) {
		return value.get() == item;
	});
	return it != m_items.end();
}