#include <QtGui/qvalidator.h>
#include "custom_field.h"

CustomField::CustomField(QWidget* parent)
	: QDialog{ parent }
	, ui{ new Ui::CustomField }
{
	ui->setupUi(this);
	QIntValidator* validator = new QIntValidator{ 1, 10000000, this };
	ui->m_width->setValidator(validator);
	ui->m_height->setValidator(validator);
	ui->m_mines->setValidator(validator);
}

int CustomField::GetWidth() const {
	return ui->m_width->text().toInt();
}

int CustomField::GetHeight() const {
	return ui->m_height->text().toInt();
}

int CustomField::GetMinesCount() const {
	return ui->m_mines->text().toInt();
}
