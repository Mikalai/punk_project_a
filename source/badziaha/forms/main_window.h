#include "main_window.ui.h"

class InventoryForm;
class World;
class CityTask;
struct WeatherStamp;

class MainWindow : public QMainWindow {
	Q_OBJECT
public:
	MainWindow();
	virtual ~MainWindow();

	World* world() { return m_world; }

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
	//InventoryForm* m_inventory{ nullptr };
	QTimer* m_timer{ nullptr };
	World* m_world{ nullptr };
};