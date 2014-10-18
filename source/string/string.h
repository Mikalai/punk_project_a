#ifndef _H_PUNK_STRING
#define _H_PUNK_STRING

#ifdef USE_QT
#include <QString>
#endif

#include <cstdint>
#include <config.h>
#include <string>

PUNK_ENGINE_BEGIN
namespace Core
{

#ifdef USE_QT
    using String = QString;
#else
    namespace __private {
    struct StringImpl;
    }

    class Buffer;
    class StringList;

    class PUNK_ENGINE_API String {
    public:
        String();
        String(const char* s);
        String(const wchar_t* s);
        String(const char* s, std::uint32_t length);
        String(const wchar_t* s, std::uint32_t length);
        String(const String& s);
        String(char s, std::uint32_t count);
        String(wchar_t s, std::uint32_t count);
        explicit String(std::uint32_t length);
        ~String();

        String& operator = (const String&);
        String& operator = (const wchar_t*);
        String& operator = (const char*);
        String& operator += (const String&);
        String& operator += (const char*);
        String& operator += (const wchar_t*);

        wchar_t& operator [] (std::uint32_t index);
        wchar_t operator [] (std::uint32_t index) const;

        std::uint32_t Length() const;
        std::uint32_t Size() const;
        String& Erase(int start, int len);
        String& Insert(char chr, int pos);
        String& Insert(wchar_t chr, int pos);
        const String Replace(const String& what, const String& with) const;
        const String SubString(int start, int count) const;
        const String Trim(const char* delimiters) const;
        const StringList Split(const char *delimiters) const;
        bool EndWith(const String& value) const;
        bool StartWith(const String& value) const;
        const char* Data() const;
        char* Data();
        Buffer ToAscii() const;
        Buffer ToWchar() const;
        void ToWchar(wchar_t* buffer, int size) const;
        Buffer ToUtf8() const;
        int ToInt32() const;
        int ToInt32FromHex() const;
        float ToFloat() const;
        double ToDouble() const;
        const String ToLower() const;
        const String ToUpper() const;
		const std::wstring toStdWString() const;

        String& arg(std::int8_t value);
        String& arg(std::uint8_t value);
        String& arg(std::int16_t value);
        String& arg(std::uint16_t value);
        String& arg(std::int32_t value);
        String& arg(std::uint32_t value);
        String& arg(std::uint64_t value);
        String& arg(std::int64_t value);
        String& arg(float value);
        String& arg(double value);
        String& arg(const String& value);
        String& arg(bool value);
        String& arg(const char* value);

        static const String Convert(std::int32_t value, int radix = 10);
        static const String Convert(std::uint32_t value, int radix = 10);
        static const String Convert(std::int64_t value, int radix = 10);
        static const String Convert(std::uint64_t value, int radix = 10);
        static const String Convert(std::int16_t value, int radix = 10);
        static const String Convert(std::uint16_t value, int radix = 10);
        static const String Convert(std::int8_t value, int radix = 10);
        static const String Convert(std::uint8_t value, int radix = 10);
        static const String Convert(float value, int precision = 5);
        static const String Convert(double value, int precision = 5);
        static const String Convert(long double value, int precision = 5);
        static const String Convert(wchar_t value);
        static const String Convert(bool value);
        static const String Convert(void* value);
        static const String FromUtf8(const Buffer& buffer);
		static const String FromUtf16(const char16_t* buffer);
		static const String fromUtf16(const char16_t* buffer) {
			return FromUtf16(buffer);
		}

        String* Clone() const;

        __private::StringImpl* impl;
    };

    PUNK_ENGINE_API bool operator == (const String& l, const String& r);
    PUNK_ENGINE_API bool operator != (const String& l, const String& r);
    PUNK_ENGINE_API const String operator + (const String& l, const String& r);
    PUNK_ENGINE_API bool operator < (const String& l, const String& r);
#endif

}
PUNK_ENGINE_END

#endif
