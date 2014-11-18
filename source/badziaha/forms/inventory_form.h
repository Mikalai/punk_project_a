#ifndef INVETORY_FORM_H2
#define INVETORY_FORM_H2

#include <QtWidgets/qwidget.h>

namespace Ui {
    class InventoryForm;
}

class Character;

class InventoryForm : public QWidget
{
    Q_OBJECT

public:
    explicit InventoryForm(QWidget *parent = 0);
    ~InventoryForm();

public slots:
	void toggle(Character*);

private:
	void updateUi();

private:
    Ui::InventoryForm *ui;
	Character* m_character{ nullptr };
};

#endif // INVETORY_FORM_H2
