#include <QtGui/qpainter.h>
#include "weather.h"
#include "global_field.h"
#include "constants.h"
#include "Character.h"
#include "items.h"
#include "unit_graphics_item.h"

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

Character::Character(GlobalField* field, QObject* parent)
	: Entity{field, parent }
{}

void Character::update() {
	Entity::update();
	auto dt = Entity::getTimeStep();

	m_body.update(dt);

	processTasks();
}

void Character::processTasks() {
	if (m_tasks.empty())
		return;
	auto& task = m_tasks.top();
	if (task.type == TaskType::Drink) {

	}
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
		auto k = p.relativeWeight();
		auto v = p.windProtection();
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
		R += r * projectedSurface() * s.power(character()->weather(), character()->fullPosition());
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

BodyPart::~BodyPart() {
	delete m_clothes;
	m_clothes = nullptr;
}

Body::~Body() {

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
		auto w = p.relativeWeight();
		auto v = p.heatAbsorbingFactor();
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