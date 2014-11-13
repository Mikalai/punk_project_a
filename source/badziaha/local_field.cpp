#include <QtCore/qpoint.h>
#include <QtWidgets/qgraphicsview.h>
#include <QtGui/qevent.h>
#include <QtCore/qfile.h>
#include <QtWidgets/qgraphicssceneevent.h>
#include <QtCore/qdir.h>
#include <QtCore/qstandardpaths.h>
#include <QtGui/qpainter.h>
#include <fstream>
#include <QtWidgets/qgraphicsitem.h>
#include "local_field.h"
#include "global_field.h"
#include "global_field_cell.h"
#include "resources.h"
#include "keys.h"
#include "unit.h"
#include "unit_item.h"
#include "character.h"

class LocalFieldCell {
public:
	LocalFieldCell()
	{}

	QPoint position() const { return m_position; };

	void setPosition(QPoint value) {
		m_position = value;
	}

	void setGlobalCell(GlobalFieldCell* cell) {
		m_cell = cell;
	}

	GlobalFieldCell* globalCell() {
		return m_cell;
	}

private:
	QPoint m_position;
	GlobalFieldCell* m_cell{ nullptr };
};

class LocalFieldCellItem : public QGraphicsItem {
public:

	LocalFieldCellItem(LocalFieldCell* cell, QGraphicsItem* parent)
		: QGraphicsItem{ parent }
		, m_cell{ cell }
	{
		QMatrix m;
		m.translate(cell->position().x()*LocalField::cellSize(), cell->position().y()*LocalField::cellSize());
		setTransform(QTransform{ m });
		setZValue(0.0f);
	}

	QRectF boundingRect() const override {
		auto size = LocalField::cellSize();
		return QRectF{ -size / 2, -size / 2, size, size };
	}

	QBrush GetGroundBrush() {
		return QBrush{ *Resources::instance()->getImage(m_cell->globalCell()->ground) };
	}

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override {
		auto size = LocalField::cellSize();
		auto brush = GetGroundBrush();
		auto pen = painter->pen();
		pen.setStyle(Qt::PenStyle::NoPen);
		painter->setPen(pen);
		painter->setBrush(brush);
		painter->drawRect(-size / 2, -size / 2, size, size);
	}

private:
	LocalFieldCell* m_cell{ nullptr };
};

class LocalField::LocalFieldImpl {
public:

	LocalFieldImpl(GlobalField* field, GlobalFieldCell* cell, LocalField* owner) 
		: m_field{ field }
		, m_cell{ cell } 
		, m_owner{ owner } {

	}

	~LocalFieldImpl() {
		while (m_units.empty()) {

		}
	}

	void create(int width, int height) {
		m_width = width;
		m_height = height;

		m_cells.resize(m_width*m_height);
		for (int y = 0; y < m_height; ++y) {
			for (int x = 0; x < m_width; ++x) {
				auto cell = &m_cells[x + y *m_width];
				cell->setPosition(QPoint{ x, y });
				cell->setGlobalCell(m_cell);
				LocalFieldCellItem* item = new LocalFieldCellItem{ cell, nullptr };
				m_owner->addItem(item);
			}
		}

		//	create temporary unit
		Unit* unit = new Unit{ m_owner, new Character{ m_owner->field(), m_owner }, 1, m_owner };
		unit->character()->setHumanControl(true);
		//unit->setPosition(QPointF{ 1, 1 });
		addUnit(unit);

		for (auto view : m_owner->views()) {
			view->setTransformationAnchor(QGraphicsView::ViewportAnchor::AnchorViewCenter);
			view->scale(15, 15);
			view->centerOn(unit->model());
		}
	}

	void addUnit(Unit* unit) {
		auto it = std::find(m_units.begin(), m_units.end(), unit);
		if (it != m_units.end()) {
			qDebug("Can't add unit. Already added");
			return;
		}
		m_units.push_back(unit);
		m_owner->addItem(unit->model());
	}

	void removeUnit(Unit* unit) {
		auto it = std::find(m_units.begin(), m_units.end(), unit);
		if (it == m_units.end()) {
			qDebug("Can't remove unit from local field. not added");
			return;
		}
		m_units.erase(it);
		m_owner->removeItem(unit->model());
	}

	void update() {
		for (auto unit : m_units) {
			unit->update();
		}
	}

	void load(std::istream& stream) {

	}

	void save(std::ostream& stream) {

	}


	int m_width{ 0 };
	int m_height{ 0 };
	LocalField* m_owner{ nullptr };
	GlobalField* m_field{ nullptr };
	GlobalFieldCell* m_cell{ nullptr };

	std::vector<LocalFieldCell> m_cells;
	std::vector<Unit*> m_units;
};

LocalField::LocalField(GlobalField* field, GlobalFieldCell* cell, QObject* parent)
	: QGraphicsScene{ parent }
	, impl{ new LocalFieldImpl{ field, cell, this } }
{
	/*if (hasStoredData(cell)) {
		load();
	}
	else {
		impl->create(64, 64);
	}*/
}

void LocalField::load() {
	auto filename = getFilename(globalCell());
	std::ifstream stream{ filename.toStdWString(), std::ios::binary };
	if (stream.is_open())
		impl->load(stream);
}

void LocalField::save() {
	auto filename = getFilename(globalCell());
	std::ofstream stream{ filename.toStdWString(), std::ios::binary };
	if (stream.is_open())
		impl->save(stream);
}

LocalField::~LocalField() {
	//save();
	impl.reset(nullptr);
}

float LocalField::cellSize() {
	return 256;
}

bool LocalField::hasStoredData(GlobalFieldCell* cell) {
	auto filename = getFilename(cell);
	return QFile::exists(filename);
}

QString LocalField::getFilename(GlobalFieldCell* cell) {
	auto path = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
	QDir dir{ path };
	if (!dir.exists("Badziaha"))
		dir.mkdir("Badziaha");
	dir.cd("Badziaha");
	auto filepath = dir.absoluteFilePath("cell_" + QString::number(cell->position.x()) + "_" + QString::number(cell->position.y()) + ".cell");
	return filepath;
}

LocalFieldCell* LocalField::cell(int x, int y) {
	return &impl->m_cells[x + width()*y];
}

LocalFieldCell* LocalField::cell(QPoint pos) {
	return cell(pos.x(), pos.y());
}

GlobalFieldCell* LocalField::globalCell() {
	return impl->m_cell;
}

int LocalField::width() const {
	return impl->m_width;
}

int LocalField::height() const {
	return impl->m_height;
}

void LocalField::keyPressEvent(QKeyEvent *event) {
	qDebug(__FUNCTION__);
	Keys::instance()->setKeyboard(event->key(), true);
	event->accept();
}

void LocalField::keyReleaseEvent(QKeyEvent *event) {
	qDebug(__FUNCTION__);
	Keys::instance()->setKeyboard(event->key(), false);
	event->accept();
}

void LocalField::mousePressEvent(QGraphicsSceneMouseEvent *event) {
	qDebug(__FUNCTION__);
	Keys::instance()->setMouse(event->button(), true);
	event->accept();
}

void LocalField::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
}

void LocalField::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
	qDebug(__FUNCTION__);
	Keys::instance()->setMouse(event->button(), false);
	event->accept();
}

GlobalField* LocalField::field() {
	return impl->m_field;
}

void LocalField::update() {
	impl->update();
}

void LocalField::create(int w, int h) {
	impl->create(w, h);
}

float LocalField::cellPhysicalSize() {
	return 256;
}