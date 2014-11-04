#include "raw_material_type.h"
#include <QtCore/qobject.h>
#include <QtCore/qstring.h>

const QString asText(RawMaterialType value) {
	switch (value)
	{
	case RawMaterialType::Water:
		return QObject::tr("Water");
	case RawMaterialType::Food:
		return QObject::tr("Food");
	case RawMaterialType::Wood:
		return QObject::tr("Wood");
	default:
		return QObject::tr("[BAD_RAW_MATERIAL]");
	}
}