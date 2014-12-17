#ifndef _H_MAIN_WINDOW
#define _H_MAIN_WINDOW

#include "main_window.ui.h"

class MainWindow : public QMainWindow {
	Q_OBJECT
public:
	MainWindow();
	virtual ~MainWindow();


public slots:
	void createField();

private:

private:
	Ui::MainWindow* ui;
};

#endif	//	_H_MAIN_WINDOW