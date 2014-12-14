#include "world.h"
#include "global_field.h"
#include "local_field.h"
#include "character.h"

void World::create() {
	m_current_time = QDateTime(QDate(2012, 7, 6), QTime(21, 30, 0));
	destroy();

	m_global_field = new GlobalField{ this, this };
	m_global_field->Create();
}

World::~World() {
	m_local_field = nullptr;
	m_global_field = nullptr;
}

void World::destroy() {
	if (m_global_field) {
		m_global_field->terminate();
		delete m_global_field;
	}
}

void World::updateByTimer() {
	TimeDependent::update();
	auto dt = getTimeStep();
	static float t = 0;
	t += dt;
	if (t >= 1.0f) {
		m_current_time = m_current_time.addSecs(t);
		m_current_weather = Temperature::instance()->weather(m_current_time);
		emit weatherChanged(m_current_weather);
		t = 0;
		emit timeChanged(m_current_time);
	}

	if (localField()) {
		localField()->update();
	}

	if (globalField()) {
		globalField()->update();
	}
}

void World::setLocalField(LocalField* value) {
	if (m_local_field)
		delete m_local_field;
	m_local_field = value;
}

void World::addCharacter(CharacterPtr value) {
	if (value->isHumanControl()) {
		if (m_player) {
			m_player->setHumanControl(false);
		}
		m_player = value.get();
	}	
	auto pos = value->pos();
	globalField()->addCharacterInstance(pos, std::move(value));	
}
