#include "time_dependent.h"

TimeDependent::TimeDependent() {
	m_last_update = std::chrono::high_resolution_clock::now();
}

void TimeDependent::update() {
	auto now = std::chrono::high_resolution_clock::now();
	m_dt = std::chrono::duration_cast<std::chrono::microseconds>(now - m_last_update).count() / float(1000000);
	m_last_update = now;
}

TimeDependent::~TimeDependent(){}