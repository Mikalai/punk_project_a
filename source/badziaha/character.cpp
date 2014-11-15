#include <QtGui/qpainter.h>
#include "weather.h"
#include "global_field.h"
#include "constants.h"
#include "Character.h"
#include "unit_graphics_item.h"

Character::Character(GlobalField* field, QObject* parent)
	: Entity{field, parent }
{}

void Character::update() {
	Entity::update();
	auto dt = Entity::getTimeStep();

	m_body.update(dt);
}

float Body::metabolismPower() const {
	auto A = ActivityClass::instance()->powerConsume(character()->activity());
	auto S = surface();
	auto C = metabolismConstant();
	auto M = A + S*C;
	return M;
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
	auto C = s * p * kc * (tskin - tenv);
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
	if (building()) {
		//return building()->heatSources(fullPosition());
	}
	else if (field()) {
		res.push_back(HeatSource{});
	}
	return res;
}