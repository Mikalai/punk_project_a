#include "surface_type.h"

QImage SurfaceTypeClass::icon() const { 
	if (m_icon.isNull()) {
		m_icon = QImage{ m_icon_path };
	}
	return m_icon;
}

void destroy(SurfaceTypeClass* value) {
	delete value;
}