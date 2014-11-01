#ifndef _H_RECORDS_WINDOW
#define _H_RECORDS_WINDOW

#include "records_window.ui.h"

class RecordsWindow : public QDialog {
	Q_OBJECT
public:
	RecordsWindow(QWidget* parent = nullptr);
	Ui::RecordsWindow* ui{ nullptr };
};

#endif	//	_H_RECORDS_WINDOW