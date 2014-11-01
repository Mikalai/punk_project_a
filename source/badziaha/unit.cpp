#include <QtGui/qpainter.h>
#include "unit.h"
#include "unit_graphics_item.h"

Unit::Unit(GlobalField* field, QObject* parent)
	: Entity{field, parent }
{}

Unit* Unit::create(GlobalField* field, UnitType type, QObject* parent) {
	auto u = new Unit{field, parent };
	if (type == UnitType::Worker) {
		qDebug("Worker create...");
		u->m_builder_level = 1;
		u->setModel(new UnitGraphicsItem<Unit, ModelType::Worker>(u, nullptr));
	}
	else if (type == UnitType::Warrior) {
		qDebug("Warrior create...");
		u->m_warrior_level = 1;
		u->setModel(new UnitGraphicsItem<Unit, ModelType::Warrior>(u, nullptr));
	}
	return u;
}