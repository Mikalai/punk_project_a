//#include <QtOpenGL/QGlWidget>
#include <qtcore/qdebug.h>
#include <QtCore/qtimezone.h>
#include <QtCore/qtimer.h>
#include <QtOpenGL/qgl.h>
#include <QtCore/qdatetime.h>
#include "main_window.h"
#include "inventory_form.h"
#include "../options.h"
#include "../world.h"
#include "../global_field.h"
#include "../global_field_cell.h"
#include "../local_field.h"
#include "../squad.h"
#include "../weather.h"
#include "../unit.h"
#include "../character.h"

MainWindow::MainWindow()
	: QMainWindow{ nullptr }
	, ui{ new Ui::MainWindow }
{
	ui->setupUi(this);
	ui->m_city_widget->hide();	
	ui->m_render_view->setViewport(new QGLWidget{ QGLFormat{ QGL::DoubleBuffer | QGL::DepthBuffer | QGL::Rgba } });
	ui->m_render_view->setViewportUpdateMode(QGraphicsView::ViewportUpdateMode::FullViewportUpdate);
	ui->m_render_view->setMouseTracking(true);

	//m_inventory = new InventoryForm{ this };
	ui->m_inventory->hide();

	QDateTime date{ QDate{ 1, 1, 1 }, QTime{ 1, 1, 1, 1 }, QTimeZone{} };

	ui->m_time->setMinimumDate{ QDate{ 100, 1, 1 } };
	ui->m_time->setDate{ QDate{ 2014, 1, 1 } };

	//ui->m_render_view->setViewport(new QGLWidget(
	//	QGLFormat(QGL::SampleBuffers)));
	//ui->m_render_view->setViewportUpdateMode(
	//	QGraphicsView::FullViewportUpdate);
}

MainWindow::~MainWindow() {
	delete m_world;
	m_world = nullptr;	
}

void MainWindow::save() {
	qDebug(__FUNCTION__);
}

void MainWindow::load() {
	qDebug(__FUNCTION__);
}

void MainWindow::quickLoad() {
	qDebug(__FUNCTION__);
}

void MainWindow::quickSave() {
	qDebug(__FUNCTION__);
}

void MainWindow::newGame() {
	qDebug(__FUNCTION__);

	if (m_world) {
		delete m_world;
	}

	m_world = new World{};	

	if (m_timer)
		delete m_timer;

	m_timer = new QTimer{ this };
	m_timer->setInterval(0);
	m_timer->setSingleShot(false);

	m_world->create();

	ui->m_render_view->setScene(m_world->globalField());
	auto s = GLOBAL_FIELD_SIZE / (float)GLOBAL_FIELD_CELL_REAL_SIZE;
	ui->m_render_view->scale(s, s);

	connect(m_timer, SIGNAL(timeout()), this, SLOT(update()));
	connect(m_world->globalField(), SIGNAL(citySelected(City*)), ui->m_city_widget, SLOT(setCity(City*)));
	connect(m_world->globalField(), SIGNAL(fieldCellPressed(QGraphicsSceneMouseEvent*, GlobalFieldCell*)), ui->m_city_widget, SLOT(selectFieldCell(QGraphicsSceneMouseEvent*, GlobalFieldCell*)));
	connect(m_world, SIGNAL(timeChanged(const QDateTime&)), ui->m_time, SLOT(setDateTime(const QDateTime&)));
	connect(m_world, SIGNAL(weatherChanged(const WeatherStamp&)), this, SLOT(weatherChanged(const WeatherStamp&)));

	m_timer->start();
}


void MainWindow::closeEvent(QCloseEvent* e) {
	if (m_timer) {
		delete m_timer;
		m_timer = nullptr;
	}

	if (m_world) {
		m_world->destroy();
		delete m_world;
		m_world = nullptr;
	}
	QMainWindow::closeEvent(e);
}

void MainWindow::enterLocation() {
	auto player = world()->player();
	if (!player) {
		qDebug("No player. Will not enter any location");
		return;
	}
	auto global_pos = player->scenePos();
	qDebug() << "Player global position:" << global_pos.x() << global_pos.y();
	auto cell = world()->globalField()->cell(global_pos);
	auto local_pos = global_pos * cell->sceneMatrix().inverted();
	qDebug() << "Player local position:" << local_pos.x() << local_pos.y();
	if (cell) {
		world()->globalField()->removeItem(player);
		auto v = std::unique_ptr < LocalField > { new LocalField{ world()->globalField(), cell, this }};
		connect(v.get(), SIGNAL(toggleInventory(Character*)), ui->m_inventory, SLOT(toggle(Character*)));
		ui->m_render_view->setScene(v.get());
		auto s = GLOBAL_FIELD_SIZE / (float)GLOBAL_FIELD_CELL_REAL_SIZE;
		ui->m_render_view->resetTransform();
		v->create(64, 64);
		auto cell = v->cell(local_pos);
		local_pos = local_pos * cell->sceneMatrix().inverted();
		qDebug() << "Player local local position:" << local_pos.x() << local_pos.y();
		world()->player()->setParentItem(cell);
		world()->player()->setPos(local_pos);	
		world()->setLocalField(v.release());
		if (player)
			ui->m_render_view->centerOn(player);
	}
}

void MainWindow::leaveLocation() {
	ui->m_render_view->setScene(world()->globalField());
	auto player = world()->globalField()->player();
	//if (player)
	//	ui->m_render_view->centerOn(player->model());
	auto s = GLOBAL_FIELD_SIZE / (float)GLOBAL_FIELD_CELL_REAL_SIZE;
	ui->m_render_view->resetTransform();
	ui->m_render_view->scale(s, s);
}

void MainWindow::setTimeScale(int value) {
	Options::instance()->setOption(OptionType::TimeScale, (float)value);
}

void MainWindow::update() {
	m_world->updateByTimer();	
}

void MainWindow::weatherChanged(const WeatherStamp& value) {
	ui->m_weather->setText(value.toString());
}

void MainWindow::createCharacter() {
	auto c = make_ptr(new Character{ world()->globalField(), nullptr });
	c->setHumanControl(true);
	c->setPos(1000000, 1000000);
	world()->addCharacter(std::move(c));
}