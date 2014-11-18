
#include <QtCore/qabstractitemmodel.h>
#include "../character.h"
#include "../items.h"
#include "inventory_form.h"
#include "inventory_form.ui.h"

class InventoryModel : public QAbstractTableModel {
public:
	InventoryModel(ItemClassType type, Character* character, QObject* parent = nullptr)
		: QAbstractTableModel{ parent }
		, m_type{ type }
		, m_character{ character }
	{
		m_cache = m_character->selectItems(m_type);
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
		if (role == Qt::DecorationRole) {
			int i = index.row() * m_column_count + index.column();
			if (i < m_cache.size()) {
				auto icon = QIcon{ QPixmap::fromImage(*m_cache[i]->icon()) };
				return QVariant{ icon };
			}
		}
		else if (role == Qt::SizeHintRole) {
			return QSize{ 64, 64 };
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

private:
	int m_column_count{ 4 };
	std::vector<const Item*> m_cache;
	Character* m_character{ nullptr };
	ItemClassType m_type{ ItemClassType::Trash };
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
	ui->m_clothes_view->setModel(new InventoryModel{ ItemClassType::Clothes, m_character, this });	
}