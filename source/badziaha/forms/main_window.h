#include "main_window.ui.h"

class GlobalField;
class LocalField;
class CityTask;
struct WeatherStamp;

class MainWindow : public QMainWindow {
	Q_OBJECT
public:
	MainWindow();
	virtual ~MainWindow();

public slots:
	void save();
	void load();
	void quickSave();
	void quickLoad();
	void newGame();
	void enterLocation();
	void leaveLocation();
	void setTimeScale(int value);
	void update();
	void weatherChanged(const WeatherStamp& value);

protected:

	void closeEvent(QCloseEvent* e) override;

private:

private:
	Ui::MainWindow* ui;
	QTimer* m_timer{ nullptr };
	GlobalField* m_global_field{ nullptr };
	std::unique_ptr<LocalField> m_local_field{ nullptr };
};