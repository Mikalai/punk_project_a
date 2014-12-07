#ifndef _ITEM_CLASS_TYPE
#define _ITEM_CLASS_TYPE

#include <QtCore/qstring.h>

enum class ItemClassType {
	Trash,
	Bottle,
	ClothesClass,
	Ammo,
	Weapon,
	Bag,
	WeaponClip,
	End
};

const QString asString(ItemClassType value);
ItemClassType ItemClassTypeFromString(const QString& value);

#endif	//	_ITEM_CLASS_TYPE