#include "main_window.ui.h"

class GlobalField;

class MainWindow : public QMainWindow {
	Q_OBJECT
public:
	MainWindow();

public slots:
	void save();
	void load();
	void quickSave();
	void quickLoad();
	void newGame();

protected:

	void closeEvent(QCloseEvent* e) override;

private:

private:
	Ui::MainWindow* ui;
	QTimer* m_timer{ nullptr };
	GlobalField* m_global_field{ nullptr };
};