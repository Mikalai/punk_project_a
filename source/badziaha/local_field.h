#ifndef _H_LOCAL_FIELD
#define _H_LOCAL_FIELD

#include <iosfwd>
#include <memory>
#include <QtWidgets/qgraphicsscene.h>
#include "surface_type.h"

class Character;
class GlobalField;
struct GlobalFieldCell;
class LocalFieldCell;
class Unit;

class LocalField : public QGraphicsScene {
	Q_OBJECT
public:
	LocalField(GlobalField* field, GlobalFieldCell* cell, QObject* parent = nullptr);
	virtual ~LocalField();

	GlobalField* field();
	GlobalFieldCell* globalCell();
	LocalFieldCell* cell(int x, int y);
	LocalFieldCell* cell(QPoint pos);

	//	size in pixels
	static float cellSize();
	//	size in meters
	static float cellPhysicalSize();

	int width() const;
	int height() const;

	void addUnit(Unit* unit);
	void removeUnit(Unit* unit);

	void update();

	void create(int w, int h);

	void centerOn(const QPointF& target);

signals:
	void toggleInventory(Character*);

protected:
	void keyPressEvent(QKeyEvent *event) override;
	void keyReleaseEvent(QKeyEvent *event) override;
	void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
	void updateViews();
	void load();
	void save();
	bool hasStoredData(GlobalFieldCell* cell);
	QString getFilename(GlobalFieldCell* cell);
public:
	class LocalFieldImpl;
	std::unique_ptr<LocalFieldImpl> impl;	
};

#endif	//	_H_LOCAL_FIELD