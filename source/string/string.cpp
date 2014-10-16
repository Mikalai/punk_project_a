#include <locale>
#include <string.h>
#include <sstream>
#include <clocale>
#include <cctype>
#include <vector>
#include <algorithm>
#include <wchar.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <exception>
#include <istream>
#include <ostream>
#include "string.h"
#include "buffer.h"
#include "string_error.h"
#include "string_list.h"

PUNK_ENGINE_BEGIN
namespace Core {

#ifndef USE_QT
    namespace __private
    {
    struct StringImpl : public std::wstring {
        using std::wstring::basic_string;
        StringImpl& operator = (const std::wstring& value)
        {
            std::wstring::operator=(value);
            return *this;
        }
    };
    }

	/*bool ConvertByteArray(const char* from, const char* to, void* inp, std::uint32_t inp_size, void* outp, std::uint32_t* outp_size)
    {
#ifdef WIN32
        if (!strcmp(from, "WCHAR_T") && !strcmp(to, "UTF8"))
        {
            if (!outp)
            {
                *outp_size = WideCharToMultiByte(CP_UTF8, 0, (LPCWSTR)inp, (int)(inp_size / sizeof(wchar_t)), 0, 0, 0, 0);
                return true;
            }
            else
            {
                int output_size = (int)(*outp_size);
                WideCharToMultiByte(CP_UTF8, 0, (LPCWSTR)inp, (int)(inp_size / sizeof(wchar_t)), (LPSTR)outp, output_size, 0, 0);
                return true;
            }
        }
        else if (!strcmp(from, "ASCII") && !strcmp(to, "WCHAR_T")) {
            if (!outp) {
                *outp_size = MultiByteToWideChar(CP_ACP, 0, (LPCSTR)inp, (int)inp_size, 0, 0) * sizeof(wchar_t);
                return true;
            }
            else {
                int output_size = (int)(*outp_size);
                MultiByteToWideChar(CP_ACP, 0, (LPCSTR)inp, (int)inp_size, (LPWSTR)outp, output_size / sizeof(wchar_t));
                return true;
            }
        }
        return false;
#elif defined __gnu_linux__
        if (!outp)
        {
            std::vector<char> result(inp_size*8);
            *outp_size = result.size();
            iconv_t handle = iconv_open(to, from);
            if (handle == (iconv_t)-1)
            {
                *outp_size = 0;
                return false;
            }
            std::uint32_t initial_size = *outp_size;
            char* out = (char*)&result[0];
            if (iconv(handle, (char**)&inp, &inp_size, (char**)&out, outp_size) == (std::uint32_t)-1)
            {
                *outp_size = 0;
                return false;
            }
            std::uint32_t actual_size = initial_size - *outp_size;
            *outp_size = actual_size;
            iconv_close(handle);
        }
        else
        {
            auto handle = iconv_open(to, from);
            iconv(handle, (char**)&inp, &inp_size, (char**)&outp, outp_size);
            iconv_close(handle);
        }
        return true;
#endif
    }*/

    const String String::FromUtf8(const Buffer& buffer)
    {
        return String("");
//		std::wstring_convert<std::codecvt_utf8<wchar_t>> convert;
//		std::wstring string = convert.from_bytes((const char*)buffer.Data(), (const char*)buffer.Data() + buffer.GetSize());
//		return String(string.data(), string.size());
    }

    String& String::Erase(int start, int len)
    {
        impl->erase(impl->begin() + start, impl->begin() + start + len);
        return *this;
    }

    String& String::Insert(char chr, int pos)
    {
        impl->insert(pos, 1, chr);
        return *this;
    }

    String& String::Insert(wchar_t chr, int pos)
    {
        impl->insert(pos, 1, chr);
        return *this;
    }

    Buffer String::ToAscii() const {
        return Buffer();
//		std::wstring_convert<std::codecvt<wchar_t, char, std::mbstate_t>> convert;
//		auto string = convert.to_bytes(impl->data());
//		Buffer buffer;
//		buffer.WriteBuffer(string.data(), string.size());
//		return buffer;
    }

    Buffer String::ToWchar() const {
        if (impl) {
			Buffer buffer((std::uint32_t)((impl->size() + 1)*sizeof(wchar_t)));
            const wchar_t* data = impl->c_str();
            buffer.WriteBuffer(data, (int)(impl->size()+1)*sizeof(wchar_t));
            return buffer;
        }
        else {
            Buffer buffer(sizeof(wchar_t));
            wchar_t t = 0;
            buffer.WriteBuffer(&t, sizeof(t));
            return buffer;
        }
    }

    void String::ToWchar(wchar_t* buffer, int size) const {
        const wchar_t* data = impl->c_str();
        memcpy(buffer, data, std::min(size, (int)((impl->size()+1)*sizeof(wchar_t))));
    }

    Buffer String::ToUtf8() const {
        return Buffer();
//		std::wstring_convert<std::codecvt_utf8<wchar_t>> convert;
//		auto string = convert.to_bytes(impl->data());
//		Buffer buffer;
//		buffer.WriteBuffer(string.data(), string.size());
//        return buffer;
    }

    const String String::Replace(const String& what, const String& with) const
    {
        String res = *this;
        std::uint32_t pos = 0;
		while ((pos = (std::uint32_t)res.impl->find(*what.impl, pos)) != (std::uint32_t)__private::StringImpl::npos)
        {
            *res.impl = res.impl->replace(pos, what.Length(), *with.impl);
        }
        return res;
    }

    const String String::SubString(int start, int count) const
    {
        std::wstring s = impl->substr(start, count);
		return String(&s[0], (std::uint32_t)s.size());
    }

    std::uint32_t String::Size() const
    {
		return (std::uint32_t)impl->size()*sizeof(__private::StringImpl::value_type);
    }

    std::uint32_t String::Length() const
    {
		return (std::uint32_t)impl->size();
    }

    String::~String()
    {
        delete impl;
        impl = nullptr;
    }

    String::String()
        : impl(new __private::StringImpl)
    {}

    String::String(const wchar_t *s)
        : impl(new __private::StringImpl(s))
    {}

    String::String(const wchar_t *s, std::uint32_t length)
        : impl(new __private::StringImpl(s, length))
    {}

    String::String(std::uint32_t length)
        : impl(new __private::StringImpl(length, L' '))
    {}

    String::String(char s, std::uint32_t count)
        : impl(new __private::StringImpl(count, (wchar_t)s)) {}

    String::String(wchar_t s, std::uint32_t count)
        : impl(new __private::StringImpl(count, s)) {}

    String::String(const char* s)
        : impl(new __private::StringImpl())
    {
		if (!s)
			return;
//		std::wstring_convert<std::codecvt<wchar_t, char, std::mbstate_t>> convert;
//		*impl = convert.from_bytes(s);
    }

    String::String(const char* s, std::uint32_t length)
        : impl(new __private::StringImpl())
    {
		if (!s)
			return;
//		std::wstring_convert<std::codecvt<wchar_t, char, std::mbstate_t>> convert;
//		*impl = convert.from_bytes(s, s + length);
    }

    String::String(const String& s)
        : impl(new __private::StringImpl(*s.impl)) {}

    String& String::operator += (const String& s) {
        *impl += *s.impl;
        return *this;
    }

    String& String::operator += (const char* s) {
        String temp(s);
        *impl += *temp.impl;
        return *this;
    }

    String& String::operator += (const wchar_t* s) {
        String temp(s);
        *impl += *temp.impl;
        return *this;
    }

    String& String::operator = (const char* s)
    {
        String temp(s);
        std::swap(impl, temp.impl);
        return *this;
    }

    String& String::operator = (const wchar_t* s)
    {
        String temp(s);
        std::swap(impl, temp.impl);
        return *this;
    }

    String& String::operator = (const String& s)
    {
        String temp(s);
        std::swap(impl, temp.impl);
        return *this;
    }

    const char* String::Data() const
    {
        return (const char*)impl->c_str();
    }

    char* String::Data()
    {
        return (char*)impl->c_str();
    }

    int String::ToInt32() const
    {
        std::wistringstream stream(*impl);
        int result;
        stream >> result;
        return result;
    }

    int String::ToInt32FromHex() const
    {
        std::wistringstream stream(*impl);
        int result;
        stream >> result;
        return result;
    }

    float String::ToFloat() const
    {
        std::wistringstream stream(*impl);
        float result;
        stream >> result;
        return result;
    }

    double String::ToDouble() const
    {
        std::wistringstream stream(*impl);
        double result;
        stream >> result;
        return result;
    }

    const String String::Convert(int32_t value, int radix)
    {
        std::wstringstream stream;
        stream << (radix == 8  ? std::oct :
                                 (radix == 16 ? std::hex :
                                                std::dec)) << value;
        return String(stream.str().c_str());
    }

    const String String::Convert(uint32_t value, int radix)
    {
        std::wstringstream stream;
        stream << (radix == 8  ? std::oct :
                                 (radix == 16 ? std::hex :
                                                std::dec)) << value;
        return String(stream.str().c_str());
    }

    //	const String String::Convert(signed char value)
    //	{
    //        char buf[16];
    //		buf[0] = value;
    //		buf[1] = 0;
    //		return String(buf);
    //	}

    //	const String String::Convert(unsigned char value)
    //	{
    //        char buf[16];
    //		buf[0] = value;
    //		buf[1] = 0;
    //		return String(buf);
    //	}

    const String String::Convert(int16_t value, int radix)
    {
        std::wstringstream stream;
        stream << (radix == 8  ? std::oct :
                                 (radix == 16 ? std::hex :
                                                std::dec)) << value;
        return String(stream.str().c_str());
    }

    const String String::Convert(uint16_t value, int radix)
    {
        std::wstringstream stream;
        stream << (radix == 8  ? std::oct :
                                 (radix == 16 ? std::hex :
                                                std::dec)) << value;
        return String(stream.str().c_str());
    }

    const String String::Convert(int8_t value, int radix)
    {
        std::wstringstream stream;
        stream << (radix == 8  ? std::oct :
                                 (radix == 16 ? std::hex :
                                                std::dec)) << value;
        return String(stream.str().c_str());
    }

    const String String::Convert(uint8_t value, int radix)
    {
        std::wstringstream stream;
        stream << (radix == 8  ? std::oct :
                                 (radix == 16 ? std::hex :
                                                std::dec)) << (unsigned)value;
        return String(stream.str().c_str());
    }

    const String String::Convert(int64_t value, int radix)
    {
        std::wstringstream stream;
        stream << (radix == 8  ? std::oct :
                                 (radix == 16 ? std::hex :
                                                std::dec)) << value;
        return String(stream.str().c_str());
    }

    const String String::Convert(uint64_t value, int radix)
    {
        std::wstringstream stream;
        stream << (radix == 8  ? std::oct :
                                 (radix == 16 ? std::hex :
                                                std::dec)) << value;
        return String(stream.str().c_str());
    }

    const String String::Convert(float value, int precision)
    {
        std::wstringstream stream;
        stream.precision(precision);
        stream << value;
        return String(stream.str().c_str());
    }

    const String String::Convert(double value, int precision)
    {
        std::wstringstream stream;
        stream.precision(precision);
        stream << value;
        return String(stream.str().c_str());
    }

    const String String::Convert(long double value, int precision)
    {
        std::wstringstream stream;
        stream.precision(precision);
        stream << value;
        return String(stream.str().c_str());
    }

    const String String::Convert(wchar_t value)
    {
        std::wstringstream str;
        str << value;
        return String(str.str().c_str());
    }

    const String String::Convert(bool value)
    {
        if (value)
            return L"True";
        return L"False";
    }

    const String String::Convert(void* value)
    {
        std::wstringstream stream;
        stream << value;
        return String(stream.str().c_str());
    }

    wchar_t& String::operator [] (std::uint32_t index)
    {
        return (*impl)[index];
    }

    wchar_t String::operator [] (std::uint32_t index) const
    {
        return (*impl)[index];
    }

    const String String::Trim(const char* delimiters) const
    {
        unsigned delLength = (unsigned)strlen(delimiters);
        unsigned strLength = Length();
        unsigned start = 0;
        unsigned end = strLength;
        for (unsigned i = 0; i < strLength; i++)
        {
            bool finish = true;
            for (unsigned j = 0; j < delLength; j++)
            {
                if ((*this)[i] == delimiters[j])
                {
                    start++;
                    finish = false;
                    break;
                }
            }
            if (finish)
                break;
        }

        for (int i = strLength - 1; i >= 0; i--)
        {
            bool finish = true;
            for (unsigned j = 0; j < delLength; j++)
            {
                if ((*this)[i] == delimiters[j])
                {
                    end--;
                    finish = false;
                    break;
                }
            }
            if (finish)
                break;
        }

        return String(impl->c_str() + start, end - start);
    }

    const StringList String::Split(const char *delimiters) const
    {
        unsigned start = 0;
        unsigned end = Length();
        StringList res;
        for (unsigned i = 0; i < (unsigned)Length(); i++)
        {
            bool finish = false;
            for (unsigned j = 0; j < strlen(delimiters); j++)
            {
                if (impl->at(i) == delimiters[j])
                {
                    end = i;
                    finish = true;
                }
            }

            if (finish)
            {
                res.Push(String(impl->c_str() + start, end - start).Trim(delimiters));
                start = end + 1;
            }
        }
        if (start < (unsigned)Length())
        {
            res.Push(String(impl->c_str() + start, Length() - start).Trim(delimiters));
        }/**/
        return res;
    }

    bool operator == (const String& l, const String& r)
    {
        return operator == (*l.impl, *r.impl);
    }

    bool operator != (const String& l, const String& r)
    {
        return !(l == r);
    }

    const String operator + (const String& l, const String& r)
    {
        String s;
        *s.impl = *l.impl + *r.impl;
        return s;
    }

    const String String::ToUpper() const
    {
        String result = *this;

        std::transform(result.impl->begin(), result.impl->end(), result.impl->begin(),
                       [](const wchar_t& c) -> wchar_t {
            std::locale loc;
            return std::use_facet<std::ctype<wchar_t>>(loc).toupper(c);
        });

        return result;
    }

    const String String::ToLower() const
    {
        String result = *this;

        std::transform(result.impl->begin(), result.impl->end(), result.impl->begin(),
                       [] (const wchar_t& c) -> wchar_t {
            std::locale loc;
            return std::use_facet<std::ctype<wchar_t>>(loc).tolower(c);
        });

        return result;
    }

    bool String::EndWith(const String &value) const
    {
        auto pos = impl->rfind(*value.impl);
        return pos != __private::StringImpl::npos;
    }

    bool String::StartWith(const String &value) const
    {
        auto pos = impl->find(*value.impl);
        return pos != __private::StringImpl::npos;
    }

    String& String::arg(std::int8_t value)
    {
        String v = Convert((std::int8_t)value);
        auto start = impl->find(L'{');
        if (start == __private::StringImpl::npos)
            return *this;
        auto end = impl->find(L'}', start);
        impl->replace(start, end - start + 1, *v.impl);
        return *this;
    }

    String& String::arg(uint8_t value)
    {
        String v = Convert((std::int8_t)value);
        auto start = impl->find(L'{');
        if (start == __private::StringImpl::npos)
            return *this;
        auto end = impl->find(L'}', start);
        impl->replace(start, end - start + 1, *v.impl);
        return *this;
    }

    String& String::arg(int16_t value)
    {
        String v = Convert((std::int16_t)value);
        auto start = impl->find(L'{');
        if (start == __private::StringImpl::npos)
            return *this;
        auto end = impl->find(L'}', start);
        impl->replace(start, end - start + 1, *v.impl);
        return *this;
    }

    String& String::arg(uint16_t value)
    {
        String v = Convert((std::uint16_t)value);
        auto start = impl->find(L'{');
        if (start == __private::StringImpl::npos)
            return *this;
        auto end = impl->find(L'}', start);
        impl->replace(start, end - start + 1, *v.impl);
        return *this;
    }

    String& String::arg(int32_t value)
    {
        String v = Convert((std::int32_t)value);
        auto start = impl->find(L'{');
        if (start == __private::StringImpl::npos)
            return *this;
        auto end = impl->find(L'}', start);
        impl->replace(start, end - start + 1, *v.impl);
        return *this;
    }

    String& String::arg(uint32_t value)
    {
        String v = Convert((std::int32_t)value);
        auto start = impl->find(L'{');
        if (start == __private::StringImpl::npos)
            return *this;
        auto end = impl->find(L'}', start);
        impl->replace(start, end - start + 1, *v.impl);
        return *this;
    }
    String& String::arg(uint64_t value)
    {
        String v = Convert((std::uint64_t)value);
        auto start = impl->find(L'{');
        if (start == __private::StringImpl::npos)
            return *this;
        auto end = impl->find(L'}', start);
        impl->replace(start, end - start + 1, *v.impl);
        return *this;
    }

    String& String::arg(int64_t value)
    {
        String v = Convert((std::int64_t)value);
        auto start = impl->find(L'{');
        if (start == __private::StringImpl::npos)
            return *this;
        auto end = impl->find(L'}', start);
        impl->replace(start, end - start + 1, *v.impl);
        return *this;
    }

    String& String::arg(float value)
    {
        String v = Convert(value);
        auto start = impl->find(L'{');
        if (start == __private::StringImpl::npos)
            return *this;
        auto end = impl->find(L'}', start);
        impl->replace(start, end - start + 1, *v.impl);
        return *this;
    }

    String& String::arg(double value)
    {
        String v = Convert(value);
        auto start = impl->find(L'{');
        if (start == __private::StringImpl::npos)
            return *this;
        auto end = impl->find(L'}', start);
        impl->replace(start, end - start + 1, *v.impl);
        return *this;
    }

    String& String::arg(const String& value)
    {
        String v = value;
        auto start = impl->find(L'{');
        if (start == __private::StringImpl::npos)
            return *this;
        auto end = impl->find(L'}', start);
        impl->replace(start, end - start + 1, *v.impl);
        return *this;
    }

    String& String::arg(bool value)
    {
        String v = Convert((std::int8_t)value);
        auto start = impl->find(L'{');
        if (start == __private::StringImpl::npos)
            return *this;
        auto end = impl->find(L'}', start);
        impl->replace(start, end - start + 1, *v.impl);
        return *this;
    }

    String& String::arg(const char* value)
    {
        String v = String(value);
        auto start = impl->find(L'{');
        if (start == __private::StringImpl::npos)
            return *this;
        auto end = impl->find(L'}', start);
        impl->replace(start, end - start + 1, *v.impl);
        return *this;
    }

    bool operator < (const String& l, const String& r) {
        return *l.impl < *r.impl;
    }

    String* String::Clone() const {
        return new String(*this);
    }
#endif

}/**/
PUNK_ENGINE_END
