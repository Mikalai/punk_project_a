#ifndef _H_TIME_DEPENDENT
#define _H_TIME_DEPENDENT

#include <chrono>

class TimeDependent {
public:
	TimeDependent();
	virtual ~TimeDependent();

	virtual void update();

	float getTimeStep() const {
		return m_dt;
	}

private:
	std::chrono::high_resolution_clock::time_point m_last_update;
	float m_dt{ 0 };
};

#endif	//	_H_TIME_DEPENDENT