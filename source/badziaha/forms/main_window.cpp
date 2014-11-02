//#include <QtOpenGL/QGlWidget>
#include <QtCore/qtimer.h>
#include "main_window.h"
#include "../global_field.h"

MainWindow::MainWindow()
	: QMainWindow{ nullptr }
	, ui{ new Ui::MainWindow }
{
	ui->setupUi(this);
	ui->m_city_widget->hide();
	//ui->m_render_view->setViewport(new QGLWidget(
	//	QGLFormat(QGL::SampleBuffers)));
	//ui->m_render_view->setViewportUpdateMode(
	//	QGraphicsView::FullViewportUpdate);
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

	connect(m_timer, SIGNAL(timeout()), m_global_field, SLOT(update()));
	connect(m_global_field, SIGNAL(citySelected(City*)), ui->m_city_widget, SLOT(setCity(City*)));
	connect(m_global_field, SIGNAL(fieldCellPressed(QGraphicsSceneMouseEvent*, GlobalFieldCell*)), ui->m_city_widget, SLOT(selectFieldCell(QGraphicsSceneMouseEvent*, GlobalFieldCell*)));

	m_timer->start();
}


void MainWindow::closeEvent(QCloseEvent* e) {
	if (m_global_field)
		m_global_field->terminate();
	QMainWindow::closeEvent(e);
}