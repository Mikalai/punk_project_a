//#include <QtOpenGL/QGlWidget>
#include <QtCore/qtimezone.h>
#include <QtCore/qtimer.h>
#include <QtCore/qdatetime.h>
#include "main_window.h"
#include "../options.h"
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

	QDateTime date{ QDate{ 1, 1, 1 }, QTime{ 1, 1, 1, 1 }, QTimeZone{} };

	ui->m_time->setMinimumDate{ QDate{ 100, 1, 1 } };
	ui->m_time->setDate{ QDate{ 2014, 1, 1 } };

	//ui->m_render_view->setViewport(new QGLWidget(
	//	QGLFormat(QGL::SampleBuffers)));
	//ui->m_render_view->setViewportUpdateMode(
	//	QGraphicsView::FullViewportUpdate);
}

MainWindow::~MainWindow() {
	m_local_field.reset(nullptr);
	m_global_field = nullptr;
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

	if (m_global_field) {
		m_global_field->terminate();
		delete m_global_field;
	}

	if (m_timer)
		delete m_timer;

	m_timer = new QTimer{ this };
	m_timer->setInterval(0);
	m_timer->setSingleShot(false);

	m_global_field = new GlobalField{ this };
	m_global_field->Create();

	ui->m_render_view->setScene(m_global_field);

	connect(m_timer, SIGNAL(timeout()), this, SLOT(update()));
	connect(m_global_field, SIGNAL(citySelected(City*)), ui->m_city_widget, SLOT(setCity(City*)));
	connect(m_global_field, SIGNAL(fieldCellPressed(QGraphicsSceneMouseEvent*, GlobalFieldCell*)), ui->m_city_widget, SLOT(selectFieldCell(QGraphicsSceneMouseEvent*, GlobalFieldCell*)));
	connect(m_global_field, SIGNAL(timeChanged(const QDateTime&)), ui->m_time, SLOT(setDateTime(const QDateTime&)));
	connect(m_global_field, SIGNAL(weatherChanged(const WeatherStamp&)), this, SLOT(weatherChanged(const WeatherStamp&)));

	m_timer->start();
}


void MainWindow::closeEvent(QCloseEvent* e) {
	if (m_global_field)
		m_global_field->terminate();
	QMainWindow::closeEvent(e);
}

void MainWindow::enterLocation() {
	auto player = m_global_field->player();
	if (!player) {
		qDebug("No player. Will not enter any location");
		return;
	}
	auto cell = m_global_field->cell(player->position());
	if (cell) {
		m_local_field.reset(new LocalField{ m_global_field, cell, this });
		ui->m_render_view->setScene(m_local_field.get());
		m_local_field->create(64, 64);
	}
}

void MainWindow::leaveLocation() {
	ui->m_render_view->setScene(m_global_field);
	auto player = m_global_field->player();
	if (player)
		ui->m_render_view->centerOn(player->model());
}

void MainWindow::setTimeScale(int value) {
	Options::instance()->setOption(OptionType::TimeScale, (float)value);
}

void MainWindow::update() {
	if (m_local_field) {
		m_local_field->update();
	}

	if (m_global_field) {
		m_global_field->updateByTimer();
	}
}

void MainWindow::weatherChanged(const WeatherStamp& value) {
	ui->m_weather->setText(value.toString());
}