#ifdef WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <Windows.h>
#endif	//	_WIN32

#include <algorithm>
#include <memory.h>
#include <string/string_error.h>
#include "buffer.h"
#include "string.h"

PUNK_ENGINE_BEGIN
namespace Core {

#ifndef USE_QT
    namespace __private {
    struct BufferImpl {
        std::uint32_t m_capacity{ 0 };
        std::uint8_t* m_buffer{ nullptr };
        std::uint8_t* m_current{ nullptr };

        BufferImpl() {}

        BufferImpl(std::uint32_t size)
            : m_capacity(size)
            , m_buffer(new std::uint8_t[m_capacity])
            , m_current(m_buffer) {}

        BufferImpl(const BufferImpl& value) {
            m_capacity = value.m_capacity;
            Resize(value.GetSize());
            memcpy(m_buffer, value.m_buffer, value.GetSize());
        }

        ~BufferImpl() {
            delete[] m_buffer;
            m_buffer = m_current = nullptr;
        }

        void Reset() {
            m_current = m_buffer;
        }

        std::uint32_t LeftOpacity() {
			return (std::uint32_t)(m_capacity - (m_current - m_buffer));
        }

        void SetPosition(std::uint32_t value) {
            if (value < m_capacity)
                m_current = m_buffer + value;
            else
                m_current = m_buffer + m_capacity;
        }

		void SetOffset(std::uint32_t value, int dir) {
			if (dir == SEEK_CUR) {							
				m_current += value;
			}
			else if (dir == SEEK_END)
				m_current = m_buffer + m_capacity - value;
			else if (dir == SEEK_SET)
				m_current = m_buffer + value;
		}

        bool IsEnd() const {
            return m_current - m_buffer >= (std::ptrdiff_t)m_capacity;
        }

        std::uint32_t GetPosition() const {
			return (std::uint32_t)(m_current - m_buffer);
        }

        std::uint32_t GetSize() const {
            return m_capacity;
        }

        void SetSize(std::uint32_t value) {
			auto offset = m_current - m_buffer;
            m_capacity = value;
            if (m_buffer) {
                delete[] m_buffer;
                m_buffer = nullptr;
            }
            if (m_capacity != 0) {
                m_current = m_buffer = new unsigned char[m_capacity];
                memset(m_buffer, 0, m_capacity);
            }
			m_current = m_buffer + offset;
        }

        const String ReadLine() {
            int len = 0;
            for (unsigned char* p = m_current; *p != '\n' && *p != '\0' && p < m_buffer + m_capacity; p++, len++);
            if (len == 0)
                return String();

            String res((char*)m_current, len);
            m_current += len;
            //  skip new line
            if (*m_current == '\n')
                ++m_current;
            return res;
        }

        const String ReadWord() {
			if (m_current > m_buffer + m_capacity)
				throw Error::StringOutOfBufferRange(0);

            unsigned char* p = 0;
            for (p = m_current; (p < m_buffer + m_capacity) && (*p == '\n' || *p == '\r' || *p == '\t' || *p == ' '); p++);
            m_current = p;
            int len = 0;
            for (unsigned char* p = m_current; (p < m_buffer + m_capacity) && *p != '\n' && *p != '\r' && *p != '\t' && *p != ' ' && *p != '\0'; p++, len++);
            String res((char*)m_current, len);
            for (unsigned char* p = m_current + len; (p < m_buffer + m_capacity) && (*p == '\n' || *p == '\t' || *p == '\r' || *p == ' ' || *p == '\0'); p++, len++);
            m_current += len;
            return res;
        }

        void ReadBuffer(void* buffer, std::uint32_t size) {
            memcpy(buffer, m_current, size);
            m_current += size;
        }

        const String ReadString() {
            std::uint32_t len = Read<std::uint32_t>();
            String res((wchar_t*)m_current, len);
            m_current += len*sizeof(wchar_t);
            return res;
        }

        void WriteString(const String& value) {
            std::uint32_t len = value.Length();
            WriteBuffer(&len, sizeof(len));
            WriteBuffer((void*)value.Data(), len*sizeof(wchar_t));
        }

        void* Release() {
            void* result = m_buffer;
            m_capacity = 0;
            m_current = nullptr;
            m_buffer = nullptr;
            return result;
        }

        void Resize(std::uint32_t value) {
            std::uint8_t* tmp = new std::uint8_t[value];
            if (m_buffer)
            {
#ifdef _MSC_VER
                memcpy_s(tmp, value, m_buffer, m_capacity);
#else
                memcpy(tmp, m_buffer, m_capacity);
#endif
            }
            m_current = tmp + (m_current - m_buffer);
            delete[] m_buffer;
            m_buffer = tmp;
            m_capacity = value;
        }

        void WriteBuffer(const void* data, std::uint32_t size) {
            if (m_buffer == nullptr) {
                m_buffer = new unsigned char[size];
                m_capacity = size;
                m_current = m_buffer;
            }

            if (m_current + size > m_buffer + m_capacity)
                Resize(size + m_current - m_buffer);
#ifdef _MSC_VER
            memcpy_s(m_current, size, data, size);
#else
            memcpy(m_current, data, size);
#endif	//	_WIN32
            m_current += size;
        }

        template<class T> T Read() {
            T res = *(T*)(m_current);
            m_current += sizeof(T);
            return res;
        }
    };
    }

    Buffer::Buffer()
        : impl(new __private::BufferImpl) {}

    Buffer::Buffer(std::uint32_t size)
        : impl(new __private::BufferImpl(size)){}

    Buffer::Buffer(const Buffer& value)
        : impl(new __private::BufferImpl(*value.impl)) {}

    Buffer& Buffer::operator = (const Buffer& value) {
        Buffer temp(value);
        std::swap(impl, temp.impl);
        return *this;
    }

    Buffer::~Buffer() {
        delete impl;
        impl = nullptr;
    }

    void Buffer::Reset() {
        impl->Reset();
    }

    void Buffer::SetPosition(std::uint32_t value) {
        impl->SetPosition(value);
    }

	void Buffer::SetOffset(std::uint32_t pos, int dir) {
		impl->SetOffset(pos, dir);
	}

    bool Buffer::IsEnd() const {
        return impl->IsEnd();
    }

    std::uint32_t Buffer::GetPosition() const {
        return impl->GetPosition();
    }

    std::uint32_t Buffer::GetSize() const {
        return impl->GetSize();
    }

    void Buffer::SetSize(std::uint32_t value) {
        impl->SetSize(value);
    }

	std::uint8_t* Buffer::Data() {
        return impl->m_buffer;
    }

	const std::uint8_t* Buffer::Data() const {
        return impl->m_buffer;
    }

    std::uint64_t Buffer::ReadUnsigned64() {
        return impl->Read<std::uint64_t>();
    }

    std::int64_t Buffer::ReadSigned64() {
        return impl->Read<std::int64_t>();
    }

    std::int32_t Buffer::ReadSigned32() {
        return impl->Read<std::int32_t>();
    }

    std::uint32_t Buffer::ReadUnsigned32() {
        return impl->Read<std::uint32_t>();
    }

    std::int16_t Buffer::ReadSigned16() {
        return impl->Read<std::int16_t>();
    }

    std::uint16_t Buffer::ReadUnsigned16() {
        return impl->Read<std::uint16_t>();
    }

    std::int8_t Buffer::ReadSigned8() {
        return impl->Read<std::int8_t>();
    }

    std::uint8_t Buffer::ReadUnsigned8() {
        return impl->Read<std::uint8_t>();
    }

    const String Buffer::ReadString() {
        return impl->ReadString();
    }

    const String Buffer::ReadLine() {
        return impl->ReadLine();
    }

    const String Buffer::ReadWord() {
        return impl->ReadWord();
    }

    float Buffer::ReadReal32() {
        return impl->Read<float>();
    }

    double Buffer::ReadReal64() {
        return impl->Read<double>();
    }

    bool Buffer::ReadBoolean() {
        return impl->Read<bool>();
    }

    void Buffer::ReadBuffer(void* buffer, std::uint32_t size) {
        impl->ReadBuffer(buffer, size);
    }

    void Buffer::WriteUnsigned64(uint64_t value) {
        impl->WriteBuffer(&value, sizeof(value));
    }

    void Buffer::WriteSigned64(int64_t value) {
        impl->WriteBuffer(&value, sizeof(value));
    }

    void Buffer::WriteSigned32(int value) {
        impl->WriteBuffer(&value, sizeof(value));
    }

    void Buffer::WriteUnsigned32(unsigned value) {
        impl->WriteBuffer(&value, sizeof(value));
    }

    void Buffer::WriteSigned16(short value) {
        impl->WriteBuffer(&value, sizeof(value));
    }

    void Buffer::WriteUnsigned16(unsigned short value) {
        impl->WriteBuffer(&value, sizeof(value));
    }

    void Buffer::WriteSigned8(signed char value) {
        impl->WriteBuffer(&value, sizeof(value));
    }

    void Buffer::WriteUnsigned8(unsigned char value) {
        impl->WriteBuffer(&value, sizeof(value));
    }

    void Buffer::WriteString(const String& value) {
        impl->WriteString(value);
    }

    void Buffer::WriteReal32(float value) {
        WriteData(&value, sizeof(value));
    }

    void Buffer::WriteReal64(double value) {
        WriteData(&value, sizeof(value));
    }

    void Buffer::WriteBuffer(const void* buffer, int size) {
        WriteData(buffer, size);
    }

    void* Buffer::Release() {
        return impl->Release();
    }

    void Buffer::Resize(std::uint32_t new_size) {
        impl->Resize(new_size);
    }

    void Buffer::WriteData(const void* data, std::uint32_t size) {
        impl->WriteBuffer(data, size);
    }

    void Buffer::WriteBoolean(bool value) {
        WriteData(&value, sizeof(value));
    }
#endif
}
PUNK_ENGINE_END
