#include <list>
#include <utility>
#include "string.h"
#include "string_list.h"

PUNK_ENGINE_BEGIN
namespace Core {

#ifndef USE_QT
	namespace __private {
		struct StringListImpl {
			std::list<String> m_list;
			static String m_bad_string;
		};

		String StringListImpl::m_bad_string;
	}

	StringList::StringList()
		: impl(new __private::StringListImpl) {}

	StringList::StringList(std::initializer_list<String> s)
		: impl(new __private::StringListImpl) {
		for (const String& l : s) {
			impl->m_list.push_back(l);
		}
	}

	StringList::StringList(const String& value)
		: impl(new __private::StringListImpl) {
		impl->m_list.push_back(value);
	}

	StringList::StringList(const StringList &value)
		: impl(new __private::StringListImpl(*value.impl)) {}

	StringList& StringList::operator = (const StringList& value) {
		StringList temp(value);
		std::swap(impl, temp.impl);
		return *this;
	}

	void StringList::Push(const String &value) {
		impl->m_list.push_back(value);
	}

	void StringList::Pop() {
		impl->m_list.pop_back();
	}

	StringList::~StringList() {
		delete impl;
		impl = nullptr;
	}

	bool operator == (const StringList& l, const StringList& r) {
		return l.impl->m_list == r.impl->m_list;
	}

	const String& StringList::operator [] (std::uint32_t index) const {
		std::list<String>::iterator it = impl->m_list.begin();
		std::advance(it, index);
		return *it;
	}

	String& StringList::operator [] (std::uint32_t index) {
		if (index >= impl->m_list.size())
			return impl->m_bad_string;
		std::list<String>::iterator it = impl->m_list.begin();
		std::advance(it, index);
		return *it;
	}

	const String StringList::ToString(const String& delim) const {
		String res;
		auto last = impl->m_list.end();
		last--;
		for (auto it = impl->m_list.begin(); it != impl->m_list.end(); ++it) {
			if (it != last)
				res += *it + delim;
			else
				res += *it;
		}
		return res;
	}

	std::uint32_t StringList::Size() const {
		return (std::uint32_t)impl->m_list.size();
	}

	StringList& StringList::operator << (const String& value) {
		impl->m_list.push_back(value);
		return *this;
	}
#endif

}
PUNK_ENGINE_END
