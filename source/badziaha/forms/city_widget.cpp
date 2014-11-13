#include <QtWidgets/qgraphicssceneevent.h>
#include <QtCore/qtimer.h>
#include <QtCore/qvariant.h>
#include <QtCore/qabstractitemmodel.h>
#include "city_widget.h"
#include "../global_field.h"
#include "../buildings.h"
#include "../city.h"
#include "../city_task.h"
#include "../Character.h"

#define CITY_RESOURCES 1
#define CITY_ROADS 2
#define CITY_CharacterS 3

CityModel::CityModel(City* value, QObject* parent)
	: QAbstractItemModel{ parent }
	, m_city{ value }
	, Resources{ createIndex(0, 0, (quintptr)0) }
	, Roads{ createIndex(1, 0, (quintptr)0) }
	, Characters{ createIndex(2, 0, (quintptr)0) }
{}

void CityModel::refresh() {
	emit dataChanged(index(0, 0), index(rowCount(), columnCount()));
}

QModelIndex CityModel::index(int row, int column, const QModelIndex &parent) const {
	if (!parent.isValid())
		return createIndex(row, column, (quintptr)0);
	if (parent == Resources)
		return createIndex(row, column, CITY_RESOURCES);
	if (parent == Roads)
		return createIndex(row, column, CITY_ROADS);
	if (parent == Characters)
		return createIndex(row, column, CITY_CharacterS);
	return QModelIndex();
}

QModelIndex CityModel::parent(const QModelIndex &child) const {
	if (child.internalId() == CITY_RESOURCES)
		return Resources;
	if (child.internalId() == CITY_ROADS)
		return Roads;
	if (child.internalId() == CITY_CharacterS)
		return Characters;
	return QModelIndex{};
}

int CityModel::rowCount(const QModelIndex &parent) const {
	if (!parent.isValid())
		return 3;
	if (parent == Resources) {
		return (int)m_city->rawMaterials().size();
	}
	if (parent == Characters) {
		return (int)m_city->characters().size();
	}
	return 0;
}

int CityModel::columnCount(const QModelIndex &parent) const {
	return 2;
}

bool CityModel::hasChildren(const QModelIndex &parent) const {
	if (parent == QModelIndex{})
		return true;

	if (parent == Resources) {
		return !m_city->rawMaterials().empty();
	}
	
	if (parent == Characters) {
		return !m_city->characters().empty();
	}

	return false;
}

QVariant CityModel::data(const QModelIndex &index, int role) const {
	if (!index.isValid())
		return QVariant();

	if (role != Qt::DisplayRole)
		return QVariant();

	if (index == Resources) {
		return QObject::tr("Resources");
	}
	else if (index == Roads) {
		return QObject::tr("Roads");
	}
	else if (index == Characters){
		return QObject::tr("Characters");
	}
	else if (index.parent() == Resources) {
		if (index.column() == 0)
			return asText(enum_value<RawMaterialType>(index.row()));
		else if (index.column() == 1) {
			auto value = enum_value<RawMaterialType>(index.row());
			auto amount = m_city->rawMaterial(value);
			return QString::number((int)amount);
		}
	}
	else if (index.parent() == Characters) {
		if (index.column() == 0)
			return m_city->characters()[index.row()]->name();
		else if (index.column() == 1) {
			return QString{};
		}
	}
	return QString{};
}

CityWidget::CityWidget(QWidget* parent)
	: QWidget{ parent }
	, ui{ new Ui::CityWidget }
{
	ui->setupUi(this);
	m_timer = new QTimer{ this };
	m_timer->setInterval(1000);
	m_timer->setSingleShot(false);

	m_timer->start();
}

void CityWidget::updateModel() {
	if (!isVisible())
		return;

	auto model = ui->m_overview->model();
	if (!model)
		return;
}

void CityWidget::setCity(City* city) {
	qDebug(__FUNCTION__);
	m_city = city;
	setVisible(m_city != nullptr);
	if (m_city) {
		ui->m_name->setText(city->name());
		auto model = new CityModel{ city, this };
		connect(m_timer, SIGNAL(timeout()), model, SLOT(refresh()));
		ui->m_overview->setModel(model);
		ui->m_overview->show();
	}
}

void CityWidget::selectFieldCell(QGraphicsSceneMouseEvent* event, GlobalFieldCell* cell) {
	qDebug(__FUNCTION__);

	if (!m_city)
		return;

	if (m_new_task.get() && m_new_task->needInput()) {
		if (event->button() == Qt::MouseButton::LeftButton) {
			m_new_task->selectCell(cell);
			if (!m_new_task->needInput())
				m_city->addTask(m_new_task.release());
		}
	}
}

void CityWidget::buildRoad() {
	qDebug(__FUNCTION__);

	if (!m_city)
		return;

	m_new_task.reset(new BuildRoad{ m_city});
}

void CityWidget::buildSawmill() {	
	qDebug(__FUNCTION__);

	if (!m_city)
		return;

	auto mill = new SawMill{ m_city->field(), m_city->field() };
	mill->setCity(m_city);
	m_new_task.reset(new Build{ m_city, mill });
}