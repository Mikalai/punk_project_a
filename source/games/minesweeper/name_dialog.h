#ifndef _H_NAME_DIALOG
#define _H_NAME_DIALOG

#include "name_dialog.ui.h"

class NameDialog : public QDialog {
public:
	NameDialog(QWidget* parent = nullptr);

	const QString GetText() const {
		return ui->m_name->text();
	}

private:
	Ui::NameDialog* ui;
};

#endif	//	_H_NAME_DIALOG