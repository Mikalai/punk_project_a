#ifndef _H_PUNK_STRING_LIST
#define _H_PUNK_STRING_LIST

#include <initializer_list>
#include <cstdint>
#include "config.h"

namespace Punk
{
    namespace Engine
    {
        namespace Core
        {
            namespace __private
            {
                struct StringListImpl;
            }

            class String;

            class PUNK_ENGINE_API StringList
            {
            public:
                StringList();
                StringList(std::initializer_list<String> s);
                StringList(const StringList& value);
                StringList& operator = (const StringList& value);
                ~StringList();

                std::uint32_t Size() const;
                void Push(const String& value);
                void Pop();
                const String ToString() const;

                const String& operator [] (std::uint32_t index) const;
                String& operator [] (std::uint32_t index);

                __private::StringListImpl* impl;

                friend bool operator == (const StringList&, const StringList&);
            };

            PUNK_ENGINE_API bool operator == (const StringList& l, const StringList& r);
        }
    }
}

#endif
