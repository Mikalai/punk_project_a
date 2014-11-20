#include <QtCore/qdebug.h>
#include "item_class_type.h"

const QString asString(ItemClassType value) {
	switch (value)
	{
	case ItemClassType::Trash:
		return "Trash";
	case ItemClassType::Bottle:
		return "Bottle";
	case ItemClassType::Clothes:
		return "Clothes";
	case ItemClassType::Weapon:
		return "Weapon";
	case ItemClassType::Bag:
		return "Bag";
	case ItemClassType::Ammo:
		return "Ammo";
	default:
		break;
	}
	qDebug() << (int)value << "item class type no string representation";
	return "[ERROR]";
}

ItemClassType ItemClassTypefromString(const QString& value) {
	qDebug() << "Can't convert string to item class type";
	return ItemClassType::End;
}