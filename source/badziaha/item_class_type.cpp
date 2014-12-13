#include <QtCore/qdebug.h>
#include "item_class_type.h"

const QString asString(ItemClassType value) {
	switch (value)
	{
	case ItemClassType::Trash:
		return "Trash";
	case ItemClassType::Bottle:
		return "Bottle";
	case ItemClassType::ClothesClass:
		return "Clothes";
	case ItemClassType::Weapon:
		return "Weapon";
	case ItemClassType::Bag:
		return "Bag";
	case ItemClassType::Ammo:
		return "Ammo";
	case ItemClassType::WeaponClip:
		return "Clip";
	default:
		break;
	}
	qDebug() << (int)value << "item class type no string representation";
	return "[ERROR]";
}

ItemClassType ItemClassTypeFromString(const QString& value) {
	if (value == "Clothes")
		return ItemClassType::ClothesClass;
	if (value == "Trash")
		return ItemClassType::Trash;
	if (value == "Bottle")
		return ItemClassType::Bottle;
	if (value == "Weapon")
		return ItemClassType::Weapon;
	if (value == "Bag")
		return ItemClassType::Bag;
	if (value == "Ammo")
		return ItemClassType::Ammo;
	if (value == "Clip")
		return ItemClassType::WeaponClip;
	qDebug() << "Can't convert" << value << "to ItemClassType";
	return ItemClassType::End;
	return ItemClassType::End;
}