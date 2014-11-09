#ifndef _H_LOCAL_FIELD
#define _H_LOCAL_FIELD

#include <QtWidgets/qgraphicsscene.h>

class GlobalField;
class GlobalFieldCell;

class LocalField : public QGraphicsScene {
	Q_OBJECT
public:
	LocalField(GlobalField* field, GlobalFieldCell* cell, QObject* parent = nullptr);
	virtual ~LocalField();

	GlobalField* field() { return m_field; }
	GlobalFieldCell* cell() { return m_cell; }

public:
	GlobalField* m_field{ nullptr };
	GlobalFieldCell* m_cell{ nullptr };
};
#endif	//	_H_LOCAL_FIELD