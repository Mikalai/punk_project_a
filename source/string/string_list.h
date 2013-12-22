#ifndef _H_PUNK_STRING_LIST
#define _H_PUNK_STRING_LIST

#include <initializer_list>
#include <cstdint>
#include <config.h>

PUNK_ENGINE_BEGIN
namespace Core
{
	namespace __private {
		struct StringListImpl;
	}

	class String;

	class PUNK_ENGINE_API StringList
	{
	public:
		StringList();
		StringList(std::initializer_list<String> s);
		StringList(const StringList& value);
		StringList(const String& value);
		StringList& operator = (const StringList& value);
		~StringList();

		std::uint32_t Size() const;
		void Push(const String& value);
		void Pop();
        const String ToString(const String& delim) const;

		const String& operator [] (std::uint32_t index) const;
		String& operator [] (std::uint32_t index);

		StringList& operator << (const String& value);

		__private::StringListImpl* impl;

		friend bool operator == (const StringList&, const StringList&);
	};

	PUNK_ENGINE_API bool operator == (const StringList& l, const StringList& r);
}
PUNK_ENGINE_END

#endif
