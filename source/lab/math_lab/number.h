#ifndef _H_NUMBERS
#define _H_NUMBERS

#include <cstdint>


class Integer {
public:
	Integer()
		: m_value{ 0 }
	{}

	Integer(std::int32_t value)
		: m_value{ value }
	{}

	Integer(const Integer& value)
		: m_value{ value.m_value }
	{}



private:
	std::int32_t m_value{ 0 };
};

#endif	//	_H_NUMBERS