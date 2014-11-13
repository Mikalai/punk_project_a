#include <QtGui/qpainter.h>
#include "Character.h"
#include "unit_graphics_item.h"

Character::Character(GlobalField* field, QObject* parent)
	: Entity{field, parent }
{}

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