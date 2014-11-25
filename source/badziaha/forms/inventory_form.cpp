#include <QtCore/qdebug.h>
#include <QtGui/qpainter.h>
#include <functional>
#include <QtWidgets/qmenu.h>
#include <QtWidgets/qitemdelegate.h>
#include <QtCore/qabstractitemmodel.h>
#include "../character.h"
#include "../items.h"
#include "inventory_form.h"
#include "inventory_form.ui.h"

class CustomDelegate : public QItemDelegate {

public:
	CustomDelegate(QObject* parent) : QItemDelegate{ parent } {}

	void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
		for (int i = 0; i < enum_size<ItemClassType>::Value; ++i) {
			if (index.column() == 0 && index.internalId() == i) {
				return;
			}
		}
		QItemDelegate::paint(painter, option, index);
	}
};

class InventoryTreeModel : public QAbstractItemModel  {
public:
	InventoryTreeModel(Character* character, std::function<std::vector<const Item*>(Character*, ItemClassType)> getter, QObject* parent = nullptr)
		: QAbstractItemModel{ parent }
		, m_character{ character }
		, m_getter{ getter }
	{
		for (int i = 0; i < enum_size<ItemClassType>::Value; ++i) {
			m_items[i] = m_getter(m_character, enum_value<ItemClassType>(i));
			Tab[i] = createIndex(i, 0, (quintptr)i);
		}
	}

	int rowCount(const QModelIndex & parent = QModelIndex()) const override {
		if (!parent.isValid()) {
			return enum_size<ItemClassType>::Value;
		}
		for (int i = 0; i < enum_size<ItemClassType>::Value; ++i) {
			if (parent == Tab[i]) {
				int l = (int)m_items[i].size();
				int d = (l % m_column_count == 0) ? 0 : 1;
				return int(m_items[i].size() / m_column_count + d);
			}
		}
		return 0;
	}

	int columnCount(const QModelIndex & parent = QModelIndex()) const override {
		return m_column_count;
	}

	QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override {
		
		if (index.parent() == QModelIndex{}) {
			if (index.column() == 0) {
				if (role == Qt::DisplayRole) {
					return asString(enum_value<ItemClassType>(index.row()));
				}
				else if (role == Qt::FontRole) {
					return QFont{ "calibri", 8, QFont::Bold, false };
				}
				else if (role == Qt::ForegroundRole) {
					return QColor{ 255, 0, 0, 255 };
				}
				else if (role == Qt::SizeHintRole) {
					return QSize{ 120, 30 };
				}
			}
			return QVariant{};
		}

		auto item = getItem(index);
		if (!item)
			return QVariant{};

		if (role == Qt::DecorationRole) {
			auto image = item->icon();
			auto pixmap = QPixmap::fromImage(image);
			pixmap = pixmap.scaled(64, 64);
			if (item->quantity() != 1) {
				QPainter painter;
				painter.begin(&pixmap);
				auto brush = painter.brush();
				brush.setColor(QColor{ 255, 255, 255 });
				brush.setStyle(Qt::BrushStyle::SolidPattern);
				painter.setBrush(brush);

				auto font = painter.font();
				font.setBold(true);
				font.setPixelSize(14);
				painter.setFont(font);

				auto s = QString::number(item->quantity());
				auto l = s.length();
				painter.drawRect(64 - l * 14 - 2, 48, l * 14 + 2, 16);
				painter.drawText(64 - l * 14, 60, s);
				painter.end();
			}
			auto icon = QIcon{ pixmap };
			return icon;
		}
		else if (role == Qt::SizeHintRole) {
			return QSize{ 64, 64 };
		}
		else if (role == Qt::ToolTipRole) {
			return item->ToString();
		}
		return QVariant{};
	}

	Qt::DropActions supportedDragActions() const override {
		return Qt::MoveAction;
	}

	Qt::DropActions supportedDropActions() const override {
		return Qt::MoveAction;
	}

	bool hasChildren(const QModelIndex &parent = QModelIndex()) const override {
		if (!parent.isValid())
			return true;
		for (int i = 0; i < enum_size<ItemClassType>::Value; ++i) {
			if (Tab[i] == parent)
				return true;
		}
		return false;
	}

	QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override {
		if (!parent.isValid()) {
			return createIndex(row, column, (quintptr)row);
		}
		for (int i = 0; i < enum_size<ItemClassType>::Value; ++i) {
			if (Tab[i] == parent) {
				return createIndex(row, column, (void*)getItem(row, column, enum_value<ItemClassType>(i)));
			}
		}
		return QModelIndex{};
	}

	QModelIndex parent(const QModelIndex &child) const override {
		if (!child.isValid())
			return QModelIndex{};
		for (int i = 0; i < enum_size<ItemClassType>::Value; ++i) {
			if (Tab[i].internalId() == child.internalId())
				return QModelIndex{};
		}
		auto item = (Item*)child.internalPointer();
		if (item) {
			int index = enum_index(item->classType());
			return Tab[index];
		}
		return QModelIndex{};
	}

	/*bool dropMimeData(const QMimeData * data, Qt::DropAction action, int row, int column, const QModelIndex & parent) override {
	return true;
	}*/

	Qt::ItemFlags flags(const QModelIndex & index) const override {
		if (index.parent().isValid())
			return Qt::ItemFlag::ItemIsDragEnabled | Qt::ItemIsSelectable | Qt::ItemFlag::ItemIsEnabled;
		else 
			return Qt::ItemFlag::ItemIsDragEnabled | Qt::ItemIsDropEnabled ;
	}
	
	void update() {
		for (int i = 0; i < enum_size<ItemClassType>::Value; ++i) {
			int old_row_count = rowCount(Tab[i]);
			m_items[i] = m_getter(m_character, enum_value<ItemClassType>(i));
			int new_row_count = rowCount(Tab[i]);
			if (old_row_count < new_row_count) {
				beginInsertRows(Tab[i], old_row_count, new_row_count - 1);
				insertRows(old_row_count, new_row_count - old_row_count, Tab[i]);
				endInsertRows();
			}
			if (old_row_count > new_row_count) {
				beginRemoveRows(Tab[i], new_row_count, old_row_count - 1);
				removeRows(new_row_count, old_row_count - new_row_count, Tab[i]);
				endRemoveRows();
			}
			if (new_row_count != 0 || old_row_count != 0) {				
				emit dataChanged(index(0, 0), index(std::max(new_row_count, old_row_count) - 1, columnCount() - 1, Tab[i]));
			}
		}		
	}

	const Item* getItem(QModelIndex index) const {
		auto p = index.parent();
		if (p.isValid()) {
			auto class_type_index = p.internalId();
			auto item_index = plainIndex(index);
			if (item_index >= m_items[class_type_index].size())
				return nullptr;
			return m_items[class_type_index][item_index];
		}
		return nullptr;
	}

private:

	int plainIndex(QModelIndex index) {
		auto r = index.row() * columnCount() + index.column();
		return r;
	}
	
	const Item* getItem(int row, int column, ItemClassType type) const {
		int type_index = enum_index(type);
		int index = column + row * columnCount();
		if (index >= m_items[type_index].size())
			return nullptr;
		return m_items[type_index][index];
	}

	int plainIndex(QModelIndex index) const {
		return index.row() * m_column_count + index.column();
	}

private:
	int m_column_count{ 4 };
	Character* m_character{ nullptr };
	std::array<std::vector<const Item*>, enum_size<ItemClassType>::Value> m_items;
	std::array<QModelIndex, enum_size<ItemClassType>::Value> Tab;
	std::function<std::vector<const Item*>(Character*, ItemClassType)> m_getter;
};






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
		return int(m_cache.size() / m_column_count + d);
	}

	int columnCount(const QModelIndex & parent = QModelIndex()) const override {
		return m_column_count;
	}

	QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override {
		int i = plainIndex(index);
		if (i >= (int)m_cache.size())
			return QVariant{};
		auto item = m_cache[i];
		if (role == Qt::DecorationRole) {
			auto image = m_cache[i]->icon();
			auto pixmap = QPixmap::fromImage(image);
			pixmap = pixmap.scaled(64, 64);
			if (item->quantity() != 1) {
				QPainter painter;
				painter.begin(&pixmap);
				auto brush = painter.brush();
				brush.setColor(QColor{ 255, 255, 255 });
				brush.setStyle(Qt::BrushStyle::SolidPattern);
				painter.setBrush(brush);

				auto font = painter.font();
				font.setBold(true);
				font.setPixelSize(14);
				painter.setFont(font);

				auto s = QString::number(item->quantity());
				auto l = s.length();
				painter.drawRect(64 - l * 14 - 2, 48, l * 14 + 2, 16);
				painter.drawText(64 - l * 14, 60, s);
				painter.end();
			}
			auto icon = QIcon{ pixmap };
			return icon;
		}
		else if (role == Qt::SizeHintRole) {
			return QSize{ 64, 64 };
		}
		else if (role == Qt::ToolTipRole) {
			return m_cache[i]->ToString();
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
		return (const Clothes*)m_cache[i];
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
	//ui->m_equipped_view->setItemDelegate(new CustomDelegate{ this });
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
	auto clothes = m_character->selectItems(ItemClassType::ClothesClass);
	ui->m_clothes_view->setModel(m_inventory = new InventoryTreeModel{ m_character, [](Character* chr, ItemClassType type) {
		return chr->selectItems(type);
	}, this });
	ui->m_equipped_view->setModel(m_equipped = new InventoryTreeModel{ m_character, [](Character* chr, ItemClassType type) {
		return chr->selectEquippedItems(type);
	}, this });
	ui->m_equipped_view->expandAll();
	ui->m_clothes_view->expandAll();
}

void InventoryForm::clothesClicked(QModelIndex index) {
	if (!m_inventory)
		return;
}

void InventoryForm::customMenuRequested(QPoint point) {
	auto item = m_inventory->getItem(ui->m_clothes_view->currentIndex());
	if (!item)
		return;

	const Clothes* clothes = nullptr;
	if (item->classType() == ItemClassType::ClothesClass)
		clothes = static_cast<const Clothes*>(item);

	QMenu menu{ this };
	menu.addAction("Put on")->setData(0);
	menu.addAction("Drop")->setData(1);

	auto action = menu.exec(ui->m_clothes_view->mapToGlobal(point));
	if (action) {
		if (action->data().toInt() == 0) {
			m_character->putOn(clothes);
			m_inventory->update();
			m_equipped->update();
			ui->m_equipped_view->expandAll();
			ui->m_clothes_view->expandAll();
		}
		if (action->data().toInt() == 1)
			qDebug("Drop");
	}
	m_inventory->dataChanged(m_inventory->index(0, 0), m_inventory->index(m_inventory->rowCount() - 1, m_inventory->columnCount() - 1));
}

void InventoryForm::equippedCustomMenuRequested(QPoint point) {	
	auto item = m_equipped->getItem(ui->m_equipped_view->currentIndex());
	if (!item)
		return;

	qDebug() << "Selected" << item->name();

	QMenu menu{ this };
	menu.addAction("Put off")->setData(0);
	menu.addAction("Drop")->setData(1);

	auto action = menu.exec(ui->m_equipped_view->mapToGlobal(point));
	if (action) {
		if (action->data().toInt() == 0) {
			if (item->classType() == ItemClassType::ClothesClass) {
				m_character->putOff((Clothes*)item);
				//m_character->field();
				m_equipped->update();
				m_inventory->update();
				ui->m_equipped_view->expandAll();
				ui->m_clothes_view->expandAll();
			}
		}
		if (action->data().toInt() == 1)
			qDebug("Drop");
	}
	//m_equipped->dataChanged(m_equipped->index(0, 0), m_equipped->index(m_equipped->rowCount() - 1, m_equipped->columnCount() - 1));
}