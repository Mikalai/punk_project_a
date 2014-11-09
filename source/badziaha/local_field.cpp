#include "local_field.h"
#include "global_field.h"
#include "global_field_cell.h"

LocalField::LocalField(GlobalField* field, GlobalFieldCell* cell, QObject* parent)
	: QGraphicsScene{ parent }
	, m_field{ field }
	, m_cell{ cell }
{}

LocalField::~LocalField() {
}

