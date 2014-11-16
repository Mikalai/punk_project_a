//#include <QtOpenGL/QGlWidget>
#include <QtCore/qtimezone.h>
#include <QtCore/qtimer.h>
#include <QtOpenGL/qgl.h>
#include <QtCore/qdatetime.h>
#include "main_window.h"
#include "../options.h"
#include "../world.h"
#include "../global_field.h"
#include "../global_field_cell.h"
#include "../local_field.h"
#include "../squad.h"
#include "../weather.h"

MainWindow::MainWindow()
	: QMainWindow{ nullptr }
	, ui{ new Ui::MainWindow }
{
	ui->setupUi(this);
	ui->m_city_widget->hide();	
	ui->m_render_view->setViewport(new QGLWidget{ QGLFormat{ QGL::DoubleBuffer | QGL::DepthBuffer | QGL::Rgba } });
	ui->m_render_view->setViewportUpdateMode(QGraphicsView::ViewportUpdateMode::FullViewportUpdate);
	ui->m_render_view->setMouseTracking(true);

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
	auto player = world()->globalField()->player();
	if (!player) {
		qDebug("No player. Will not enter any location");
		return;
	}
	auto cell = world()->globalField()->cell(player->position());
	if (cell) {
		auto v = std::unique_ptr < LocalField > { new LocalField{ world()->globalField(), cell, this }};
		ui->m_render_view->setScene(v.get());
		v->create(64, 64);
		world()->setLocalField(v.release());
	}
}

void MainWindow::leaveLocation() {
	ui->m_render_view->setScene(world()->globalField());
	auto player = world()->globalField()->player();
	if (player)
		ui->m_render_view->centerOn(player->model());
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