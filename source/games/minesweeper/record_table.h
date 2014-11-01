#ifndef _H_RECORD_TABLE
#define _H_RECORD_TABLE

#include <memory>
#include <array>
#include <limits>
#include <QtCore/qstring.h>

class RecordTable {
public:

	struct Record {
		QString m_name;
		int level{ 0 };
		int m_time{ std::numeric_limits<int>::max() };
		int m_saves_count{ std::numeric_limits<int>::max() };
	};

public:

	~RecordTable();
	void Save(std::ostream& stream);
	void Load(std::istream& stream);

	void UpdateRecord(const RecordTable::Record& record);
	const Record& GetRecord(int level) {
		return m_records.at(level);
	}


	bool IsBest(const Record& r) const;
	static RecordTable* Instance();

private:
	static std::unique_ptr<RecordTable> m_instance;
	std::array<Record, 4> m_records;
};

inline bool operator < (const RecordTable::Record &l, const RecordTable::Record& r) {
	if (l.m_saves_count < r.m_saves_count)
		return true;
	return l.m_time < r.m_time;
}

#endif	//	_H_RECORD_TABLE