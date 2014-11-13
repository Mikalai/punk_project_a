#ifndef _H_STRING_EX
#define _H_STRING_EX

#include <vector>
#include <string>
#include <QtCore/qstring.h>

inline const std::wstring toWString(const QString& value) {
	int s = value.size();
	std::vector<wchar_t> buf(s);
	value.toWCharArray(buf.data());
	return std::wstring{ buf.begin(), buf.end()};
}

#endif	//	_H_STRING_EX