#ifndef _H_MAIN_FORM
#define _H_MAIN_FORM

#include "main_window.ui.h"

class Field;
class QTimer;

enum class Level {
	Easy,
	Medium,
	Hard,
	Hardcore,
	Custom
};

class MainWindow : public QMainWindow {
	Q_OBJECT
public:
		MainWindow();

public slots:
	void IncreaseTime();
	void Explode();
	void Complete();
	void SetMines(int value);
	void save();
	void load();
	void reset();
	void setEasy();
	void setMedium();
	void setHard();
	void setHardcore();
	void setCustom();
	void showRecords();
	void showAboutQt();

private:
	Ui::MainWindow* ui;
	Field* m_field{ nullptr };
	QTimer* m_timer{ nullptr };
	int m_width{ 9 };
	int m_height{ 9 };
	int m_mines_count{ 10 };
	int m_save_count{ 0 };
	Level m_level{ Level::Easy };
};
#endif