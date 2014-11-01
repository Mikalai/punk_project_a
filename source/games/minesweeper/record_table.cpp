#include <vector>
#include <iostream>
#include <fstream>
#include <QtCore/qstandardpaths.h>
#include <QtCore/qdir.h>
#include "record_table.h"

QString GetRecordsFile() {
	QString path = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
	QDir dir{ path };
	if (!dir.exists("Minesweeper"))
		dir.mkdir("Minesweeper");
	dir.cd("Minesweeper");
	auto filepath = dir.absoluteFilePath("records.dat");
	return filepath;
}

std::unique_ptr<RecordTable> RecordTable::m_instance;

void RecordTable::Save(std::ostream& stream) {

	for (int i = 0; i < 4; ++i) {
		auto& r = m_records[i];
		auto s = r.m_name.toStdWString();
		int length = s.size();
		stream.write((char*)&length, sizeof(length));
		if (length) {
			stream.write((char*)s.data(), sizeof(wchar_t) * length);
		}
		stream.write((char*)&r.m_saves_count, sizeof(r.m_saves_count));
		stream.write((char*)&r.m_time, sizeof(r.m_time));
	}
}

void RecordTable::Load(std::istream& stream) {
	for (int i = 0; i < 4; ++i) {
		auto& r = m_records[i];
		auto s = r.m_name.toStdWString();
		int length;
		stream.read((char*)&length, sizeof(length));
		if (length) {
			std::vector<wchar_t> buffer;
			buffer.resize(length);
			stream.read((char*)buffer.data(), sizeof(wchar_t) * length);
			auto s = std::wstring(buffer.begin(), buffer.end());
			r.m_name = QString::fromStdWString(s);
		}
		stream.read((char*)&r.m_saves_count, sizeof(r.m_saves_count));
		stream.read((char*)&r.m_time, sizeof(r.m_time));
	}
}

RecordTable* RecordTable::Instance() {
	if (!m_instance.get()) {
		m_instance.reset(new RecordTable);

		auto filepath = GetRecordsFile();
		std::ifstream stream(filepath.toStdString(), std::ios::binary);

		if (!stream.is_open()) {
			std::cout << "Failed to open records table file " << filepath.toStdString() << std::endl;
		}
		else {
			m_instance->Load(stream);
		}
	}

	return m_instance.get();
}

RecordTable::~RecordTable() {
	auto filepath = GetRecordsFile();

	std::ofstream stream(filepath.toStdString(), std::ios::binary);
	Save(stream);
}

bool RecordTable::IsBest(const Record& r) const {
	return r < m_records[r.level];
}

void RecordTable::UpdateRecord(const RecordTable::Record& record) {
	if (record < m_records[record.level])
		m_records[record.level] = record;
}