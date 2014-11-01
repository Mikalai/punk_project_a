#include "name_dialog.h"

NameDialog::NameDialog(QWidget* parent)
	: QDialog(parent)
{
	ui = new Ui::NameDialog;
	ui->setupUi(this);
}

