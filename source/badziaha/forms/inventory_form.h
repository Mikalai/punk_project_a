#ifndef INVETORY_FORM_H2
#define INVETORY_FORM_H2

#include <QtWidgets/qabstractitemdelegate.h>
#include <QtCore/qpoint.h>
#include <QtWidgets/qwidget.h>
#include "../fwd_items.h"

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
	Character* character() { return m_character; }

public:
	void updateModels();

private:
    Ui::InventoryForm *ui;
	Character* m_character{ nullptr };
	InventoryTreeModel* m_inventory{ nullptr };
	InventoryTreeModel* m_equipped{ nullptr };

	struct InjectClip {
		WeaponClip* clip{ nullptr };
		Weapon* weapon{ nullptr };
	};

	struct EjectClip {
		WeaponClip* clip{ nullptr };
		Weapon* weapon{ nullptr };
	};

	struct PutOn {
		Clothes* clothes{ nullptr };
	};

	struct PutOff {
		Clothes* clothes{ nullptr };
	};

	InjectClip inject_clip;
	EjectClip eject_clip;
	PutOn put_on;
	PutOff put_off;

};

#endif // INVETORY_FORM_H2
