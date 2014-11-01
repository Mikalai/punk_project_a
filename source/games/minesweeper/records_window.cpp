#include <fstream>
#include "records_window.h"
#include "record_table.h"

RecordsWindow::RecordsWindow(QWidget* parent)
	: QDialog(parent)
	, ui{ new Ui::RecordsWindow }
{
	ui->setupUi(this);
	RecordTable& table = *RecordTable::Instance();

	auto record = table.GetRecord(0);
	ui->m_easy_name->setText(record.m_name.isEmpty() ? "No" : record.m_name);
	ui->m_easy_saves->setText(record.m_saves_count == std::numeric_limits<int>::max() ? "No" : QString::number(record.m_saves_count));
	ui->m_easy_time->setText(record.m_time == std::numeric_limits<int>::max() ? "No" : QString::number(record.m_time));

	record = table.GetRecord(1);
	ui->m_medium_name->setText(record.m_name.isEmpty() ? "No" : record.m_name);
	ui->m_medium_saves->setText(record.m_saves_count == std::numeric_limits<int>::max() ? "No" : QString::number(record.m_saves_count));
	ui->m_medium_time->setText(record.m_time == std::numeric_limits<int>::max() ? "No" : QString::number(record.m_time));

	record = table.GetRecord(2);
	ui->m_hard_name->setText(record.m_name.isEmpty() ? "No" : record.m_name);
	ui->m_hard_saves->setText(record.m_saves_count == std::numeric_limits<int>::max() ? "No" : QString::number(record.m_saves_count));
	ui->m_hard_time->setText(record.m_time == std::numeric_limits<int>::max() ? "No" : QString::number(record.m_time));

	record = table.GetRecord(3);
	ui->m_hardcore_name->setText(record.m_name.isEmpty() ? "No" : record.m_name);
	ui->m_hardcore_saves->setText(record.m_saves_count == std::numeric_limits<int>::max() ? "No" : QString::number(record.m_saves_count));
	ui->m_hardcore_time->setText(record.m_time == std::numeric_limits<int>::max() ? "No" : QString::number(record.m_time));
}

