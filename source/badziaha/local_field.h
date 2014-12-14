#ifndef _H_LOCAL_FIELD
#define _H_LOCAL_FIELD

#include <iosfwd>
#include <memory>
#include <functional>
#include <QtWidgets/qgraphicsscene.h>
#include "time_dependent.h"
#include "surface_type.h"
#include "fwd_items.h"
#include "fwd_local_field.h"
#include "fwd_unit.h"
#include "field.h"

class Character;
class GlobalField;
class GlobalFieldCell;
class LocalFieldCell;
class Unit;

class LocalField : public Field, public TimeDependent {
	Q_OBJECT
public:

	LocalField(GlobalField* field, GlobalFieldCell* cell, QObject* parent = nullptr);
	virtual ~LocalField();

	GlobalField* field() const { return m_global_field; }
	GlobalFieldCell* globalCell() const { return m_global_field_cell; }
	FieldCell* cell(int x, int y) override;
	FieldCell* cell(const QPoint& pos) override;
	FieldCell* cell(const QPointF& pos);

	//	size in pixels
	static float cellSize();
	//	size in meters
	static float cellPhysicalSize();

	int width() const { return m_width; }
	int height() const { return m_height; }

	void update() override;

	void create(int w, int h);

	void centerOn(const QPointF& target);

	void addCharacterInstance(const QPointF& global_position, CharacterPtr value) override;
	void addItemInstance(const QPointF& global_position, ItemPtr item) override;
	ItemPtr removeItemInstance(const Item* item) override;
	bool hasItemInstance(const Item* item) const override;
	const std::vector<const Item*> selectItemInstances(ItemClassType type) const override;
	const std::vector<const Item*> selectItemInstances(ItemClassType type, QRectF rect) const override;

	void addUnit(UnitPtr value);

	static float realWidth();
	static float realHeight();

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
private:
	GlobalField* m_global_field{ nullptr };
	GlobalFieldCell* m_global_field_cell{ nullptr };
	float m_scale{ 1 };
	float m_max_scale{ 5.0f };
	float m_min_scale{ 0.1f };
	int m_width = 64;
	int m_height = 64;
	std::vector<LocalFieldCellPtr> m_cells;
	QPointF m_last_position;
	QPointF m_target;	
};

#endif	//	_H_LOCAL_FIELD