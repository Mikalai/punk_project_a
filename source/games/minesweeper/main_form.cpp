#include <iostream>
#include <QtWidgets/qmessagebox.h>
#include "name_dialog.h"
#include "record_table.h"
#include <QtWidgets/qprogressdialog.h>
#include <fstream>
#include <QtWidgets/qfiledialog.h>
#include <QtCore/qtimer.h>
#include "records_window.h"
#include "main_form.h"
#include "field.h"
#include "custom_field.h"

MainWindow::MainWindow()
	: QMainWindow() {
	ui = new Ui::MainWindow();
	ui->setupUi(this);

	m_timer = new QTimer(this);
	m_timer->setSingleShot(false);
	m_timer->setTimerType(Qt::TimerType::PreciseTimer);
	m_timer->setInterval(1000);
	connect(m_timer, SIGNAL(timeout()), this, SLOT(IncreaseTime()));

	setEasy();
}

void MainWindow::IncreaseTime() {
	std::cout << "Timer triggered..." << std::endl;
	if (m_field->IsExploded() || m_field->IsComplete()) {
		m_timer->stop();
		return;
	}

	ui->m_time->display(ui->m_time->intValue() + 1);
}

void MainWindow::Explode() {
	ui->m_field_view->setInteractive(false);
	ui->m_start_btn->setIcon(QIcon(":/resources/icons/head_dead.ico"));
}

void MainWindow::Complete() {
	std::cout << "You won!!!" << std::endl;
	ui->m_start_btn->setIcon(QIcon(":/resources/icons/head_win.ico"));
	ui->m_field_view->setInteractive(false);
	RecordTable::Record r;
	r.m_time = ui->m_time->intValue();
	r.m_saves_count = m_save_count;
	r.level = (int)m_level;
	if (m_level != Level::Custom) {
		auto records = RecordTable::Instance();
		if (records->IsBest(r)) {
			NameDialog name{ this };
			name.exec();
			r.m_name = name.GetText();
			records->UpdateRecord(r);
		}
	}
	m_timer->stop();
}

void MainWindow::SetMines(int value) {
	ui->m_mines_left->display(value);
}

void MainWindow::save() {
	if (m_field->IsComplete()) {
		QMessageBox::information(this, tr("No-no-no"), tr("Will not save complete game"));
		return;
	}

	if (m_field->IsExploded()) {
		QMessageBox::information(this, tr("No-no-no"), tr("Will not save failed game"));
		return;
	}

	auto filename = QFileDialog::getSaveFileName(this, "Save game", QString(), "Saved games (*.field)");
	if (filename.isEmpty())
		return;
	auto s = filename.toStdString();
	
	QProgressDialog progress(this);
	progress.setWindowModality(Qt::WindowModal);
	progress.setLabelText("Saving");
	progress.setRange(0, 5);
	progress.setWindowTitle("Saving game");
	std::ofstream stream(s, std::ios::binary);

	if (!stream.is_open())
		return;

	m_save_count++;
	progress.setValue(1);
	int time = ui->m_time->intValue();
	stream.write((char*)&time, sizeof(time));
	int mines = ui->m_mines_left->intValue();
	stream.write((char*)&mines, sizeof(mines));
	stream.write((char*)&m_save_count, sizeof(m_save_count));
	progress.setValue(2);
	m_field->Save(stream);
	progress.setValue(3);
}

void MainWindow::load() {	

	auto filename = QFileDialog::getOpenFileName(this, "Load game", QString(), "Saved games (*.field)");
	if (filename.isEmpty())
		return;

	QProgressDialog progress(this);
	ui->m_start_btn->setIcon(QIcon(":/resources/icons/head.ico"));
	progress.setWindowModality(Qt::WindowModal);
	progress.setRange(0, 5);
	progress.setWindowTitle("Loading game");
	progress.setLabelText("Loading game");

	std::ifstream stream(filename.toStdString(), std::ios::binary);
	
	if (!stream.is_open())
		return;

	progress.setValue(1);

	if (m_field)
		delete m_field;

	m_field = new Field(this);
	progress.setValue(2);
	connect(m_field, SIGNAL(started()), m_timer, SLOT(start()));
	connect(m_field, SIGNAL(explode()), m_timer, SLOT(stop()));
	connect(m_field, SIGNAL(explode()), this, SLOT(Explode()));
	connect(m_field, SIGNAL(complete()), m_timer, SLOT(stop()));
	connect(m_field, SIGNAL(complete()), this, SLOT(Complete()));
	connect(m_field, SIGNAL(minesCountChanged(int)), this, SLOT(SetMines(int)));

	int time;
	stream.read((char*)&time, sizeof(time));
	ui->m_time->display(time);
	int mines;
	stream.read((char*)&mines, sizeof(mines));
	ui->m_mines_left->display(mines);
	stream.read((char*)&m_save_count, sizeof(m_save_count));
	std::cout << "Save count " << m_save_count << std::endl;

	progress.setValue(3);
	m_field->Load(stream);

	ui->m_field_view->setInteractive(!m_field->IsExploded());
	ui->m_field_view->setScene(m_field);
	ui->m_field_view->scene()->update();

	m_timer->start();
	progress.setValue(4);
}

void MainWindow::reset() {

	m_timer->stop();
	ui->m_start_btn->setIcon(QIcon(":/resources/icons/head.ico"));
	QProgressDialog progress(this);
	progress.setWindowModality(Qt::WindowModal);
	progress.setLabelText("Creating field");
	progress.setWindowTitle("Creating field");
	progress.setRange(0, 4);

	progress.show();
	if (m_field)
		delete m_field;

	progress.setValue(1);

	m_field = new Field(this);
	progress.setValue(2);
	m_field->Create(m_width, m_height, m_mines_count);
	progress.setValue(3);
	connect(m_field, SIGNAL(started()), m_timer, SLOT(start()));
	connect(m_field, SIGNAL(explode()), m_timer, SLOT(stop()));
	connect(m_field, SIGNAL(explode()), this, SLOT(Explode()));
	connect(m_field, SIGNAL(complete()), m_timer, SLOT(stop()));
	connect(m_field, SIGNAL(complete()), this, SLOT(Complete()));
	connect(m_field, SIGNAL(minesCountChanged(int)), this, SLOT(SetMines(int)));

	//connect(field, SIGNAL(started()), this, SLOT(IncreaseTime()));

	ui->m_time->display(0);
	ui->m_field_view->setMouseTracking(true);
	ui->m_field_view->setInteractive(true);
	ui->m_field_view->setScene(m_field);

	ui->m_mines_left->display(m_mines_count);

	m_save_count = 0;
	progress.setValue(4);
}

void MainWindow::setEasy() {
	m_width = m_height = 9;
	m_mines_count = 10;
	m_level = Level::Easy;
	reset();
}

void MainWindow::setMedium() {
	m_width = m_height = 16;
	m_mines_count = 40;
	m_level = Level::Medium;
	reset();
}

void MainWindow::setHard() {
	m_width = 30;
	m_height = 16;
	m_mines_count = 99;
	m_level = Level::Hard;
	reset();
}

void MainWindow::setHardcore() {
	m_width = 1000;
	m_height = 1000;
	m_mines_count = 206250;
	m_level = Level::Hardcore;
	reset();
}

void MainWindow::setCustom() {
	CustomField field{ this };
	if (field.exec()) {
		m_width = field.GetWidth();
		m_height = field.GetHeight();
		m_mines_count = field.GetMinesCount();
		m_level = Level::Custom;
		reset();
	}
}

void MainWindow::showRecords() {
	RecordsWindow wnd;
	wnd.exec();
}

void MainWindow::showAboutQt() {
	QApplication::aboutQt();
}