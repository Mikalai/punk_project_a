#ifndef _H_CUSTOM_FIELD
#define _H_CUSTOM_FIELD

#include "custom_field.ui.h"

class CustomField : public QDialog {
	Q_OBJECT
public:
	CustomField(QWidget* parent = nullptr);

	int GetWidth() const;
	int GetHeight() const;
	int GetMinesCount() const;

private:
	Ui::CustomField* ui = nullptr;
};

#endif _H_CUSTOM_FIELD
