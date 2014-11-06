#ifndef _H_ROAD
#define _H_ROAD

#include <QtCore/qobject.h>
#include <list>
class QGraphicsItem;
class GlobalField;
struct GlobalFieldCell;

class Road : public QObject {
public:
	Road(GlobalField* field, GlobalFieldCell* start, GlobalFieldCell* end, QObject* parent = nullptr);
	virtual ~Road();

	QGraphicsItem* model() {
		return m_model;
	}

	bool split(GlobalFieldCell* cell, Road** a, Road** b);

	std::list<GlobalFieldCell*>& getPath() {
		return m_path;
	}

	//	can extend current road on one neighbour cell
	void extend(GlobalFieldCell* cell);

	void removeRoad();

	GlobalField* field() { return m_field; }

private:
	QGraphicsItem* m_model{ nullptr };
	std::list<GlobalFieldCell*> m_path;
	GlobalFieldCell* m_start{ nullptr };
	GlobalFieldCell* m_end{ nullptr };
	GlobalField* m_field{ nullptr };
};
#endif	//	 _H_ROAD