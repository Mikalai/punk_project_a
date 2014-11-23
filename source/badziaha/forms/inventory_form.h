#ifndef INVETORY_FORM_H2
#define INVETORY_FORM_H2

#include <QtWidgets/qabstractitemdelegate.h>
#include <QtCore/qpoint.h>
#include <QtWidgets/qwidget.h>

namespace Ui {
    class InventoryForm;
}

class Character;
class InventoryModel;
class InventoryTreeModel;

class InventoryForm : public QWidget
{
    Q_OBJECT

public:
    explicit InventoryForm(QWidget *parent = 0);
    ~InventoryForm();

public slots:
	void toggle(Character*);
	void clothesClicked(QModelIndex index);
	void customMenuRequested(QPoint point);
	void equippedCustomMenuRequested(QPoint point);
private:
	void updateUi();

private:
    Ui::InventoryForm *ui;
	Character* m_character{ nullptr };
	InventoryTreeModel* m_inventory{ nullptr };
	InventoryTreeModel* m_equipped{ nullptr };
};

#endif // INVETORY_FORM_H2
