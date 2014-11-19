#include <functional>
#include <QtWidgets/qmenu.h>
#include <QtCore/qabstractitemmodel.h>
#include "../character.h"
#include "../items.h"
#include "inventory_form.h"
#include "inventory_form.ui.h"

class InventoryModel : public QAbstractTableModel {
public:
	InventoryModel(std::function<std::vector<const Item*>(Character*)> func, Character* character, QObject* parent = nullptr)
		: QAbstractTableModel{ parent }
		, m_character{ character }
		, m_get_items{ func }
	{
		m_cache = m_get_items(m_character);
	}

	int rowCount(const QModelIndex & parent = QModelIndex()) const override {
		int l = (int)m_cache.size();
		int d = (l % m_column_count == 0) ? 0 : 1;
		return m_cache.size() / m_column_count + d;
	}

	int columnCount(const QModelIndex & parent = QModelIndex()) const override {
		return m_column_count;
	}

	QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override {
		int i = plainIndex(index);
		if (role == Qt::DecorationRole) {
			if (i < m_cache.size()) {
				auto icon = QIcon{ QPixmap::fromImage(*m_cache[i]->icon()) };
				return QVariant{ icon };
			}
		}
		else if (role == Qt::SizeHintRole) {
			return QSize{ 64, 64 };
		}
		else if (role == Qt::ToolTipRole) {
			QString v = "<b>" + m_cache[i]->name() + "</b><br/>";
			v += "<font color='blue'>Weight: </font>" + QString::number(m_cache[i]->weight()) + "<br/>";
			v += "<font color='blue'>Level: </font>" + QString::number(m_cache[i]->technologyLevel()) + "<br/>";
			if (m_cache[i]->classType() == ItemClassType::Clothes) {
				const Clothes* c = (Clothes*)m_cache[i];
				v += "<font color='red'>Wind protection: </font>" + QString::number(c->windProtection()) + "<br/>";
				v += "<font color='red'>Heat absorption: </font>" + QString::number(c->heatRadiationAbsorption()) + "<br/>";
				v += "<font color='red'>Water resistance: </font>" + QString::number(c->waterResistance()) + "<br/>";
			}
			v += "<br/>" + m_cache[i]->description();
			return v;
		}
		return QVariant{}; 
	}

	Qt::DropActions supportedDragActions() const override {
		return Qt::MoveAction;
	}

	Qt::DropActions supportedDropActions() const override {
		return Qt::MoveAction;
	}

	/*bool dropMimeData(const QMimeData * data, Qt::DropAction action, int row, int column, const QModelIndex & parent) override {
		return true;
	}*/

	Qt::ItemFlags flags(const QModelIndex & index) const override {
		return Qt::ItemFlag::ItemIsDragEnabled | Qt::ItemIsDropEnabled | Qt::ItemIsSelectable | Qt::ItemFlag::ItemIsEnabled;
	}

	const Clothes* clothes(QModelIndex index) const {
		int i = plainIndex(index);
		if (i >= m_cache.size())
			return nullptr;
		return (Clothes*)m_cache[i];
	}

	void update() {
		int old_row_count = rowCount();
		m_cache = m_get_items(m_character);
		int new_row_count = rowCount();
		if (old_row_count < new_row_count) {
			beginInsertRows(QModelIndex{}, old_row_count, new_row_count-1);
			insertRows(old_row_count, new_row_count - old_row_count);
			endInsertRows();
		}
		if (old_row_count > new_row_count) {
			beginRemoveRows(QModelIndex{}, new_row_count, old_row_count - 1);
			removeRows(new_row_count, old_row_count - new_row_count);
			endRemoveRows();
		}
		dataChanged(index(0, 0), index(std::max(new_row_count, old_row_count) - 1, columnCount()));
	}

private:
	
	int plainIndex(QModelIndex index) const {
		return index.row() * m_column_count + index.column();
	}

private:
	int m_column_count{ 4 };
	std::function<std::vector<const Item*>(Character*)> m_get_items;
	std::vector<const Item*> m_cache;
	Character* m_character{ nullptr };
};

InventoryForm::InventoryForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InventoryForm)
{
    ui->setupUi(this);
}

InventoryForm::~InventoryForm()
{
    delete ui;
}

void InventoryForm::toggle(Character* value) {
	qDebug(__FUNCTION__);
	if (isVisible()) {
		hide();
	}
	else {
		auto w = qobject_cast<QWidget*>(parent());
		show();		
	}
	m_character = value;	
	updateUi();
}

void InventoryForm::updateUi() {
	auto clothes = m_character->selectItems(ItemClassType::Clothes);
	ui->m_clothes_view->setModel(m_inventory = new InventoryModel{ [](Character* chr) {
		return chr->selectItems(ItemClassType::Clothes);
	}, m_character, this });
	ui->m_equipped_view->setModel(m_equipped = new InventoryModel{ [](Character* chr) {
		return chr->selectEquippedItems();
	}, m_character, this });
}

void InventoryForm::clothesClicked(QModelIndex index) {
	if (!m_inventory)
		return;
}

void InventoryForm::customMenuRequested(QPoint point) {
	auto clothes = m_inventory->clothes(ui->m_clothes_view->currentIndex());
	if (!clothes)
		return;

	QMenu menu{ this };
	menu.addAction("Put on")->setData(0);
	menu.addAction("Drop")->setData(1);

	auto action = menu.exec(ui->m_clothes_view->mapToGlobal(point));
	if (action) {
		if (action->data().toInt() == 0) {
			m_character->putOn(clothes);
			m_inventory->update();
			m_equipped->update();
		}
		if (action->data().toInt() == 1)
			qDebug("Drop");
	}
	m_inventory->dataChanged(m_inventory->index(0, 0), m_inventory->index(m_inventory->rowCount() - 1, m_inventory->columnCount() - 1));
}

void InventoryForm::equippedCustomMenuRequested(QPoint point) {
	auto clothes = m_equipped->clothes(ui->m_equipped_view->currentIndex());
	if (!clothes)
		return;

	QMenu menu{ this };
	menu.addAction("Put off")->setData(0);
	menu.addAction("Drop")->setData(1);

	auto action = menu.exec(ui->m_equipped_view->mapToGlobal(point));
	if (action) {
		if (action->data().toInt() == 0) {
			m_character->putOff(clothes);
			m_equipped->update();
			m_inventory->update();
		}
		if (action->data().toInt() == 1)
			qDebug("Drop");
	}
	m_equipped->dataChanged(m_equipped->index(0, 0), m_equipped->index(m_equipped->rowCount() - 1, m_equipped->columnCount() - 1));
}