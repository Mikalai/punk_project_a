#ifndef _H_PUNK_BUFFER
#define _H_PUNK_BUFFER

#ifdef USE_QT
#include <QByteArray>
#endif

#include <cstdint>
#include <vector>
#include <array>
#include "config.h"

PUNK_ENGINE_BEGIN
namespace Core
{
#ifdef USE_QT
    typedef QByteArray Buffer;
#else
    namespace __private
    {
    struct BufferImpl;
    }

    class String;

    class PUNK_ENGINE_API Buffer
    {
    public:

        Buffer();
        Buffer(const Buffer& value);
        Buffer& operator = (const Buffer& value);
        Buffer(std::uint32_t size);
        ~Buffer();
        void SetPosition(std::uint32_t pos);
		void SetOffset(std::uint32_t pos, int dir);
        std::uint32_t GetPosition() const;
        std::uint32_t GetSize() const;
        void SetSize(std::uint32_t size);
        std::uint8_t* Data();
		const std::uint8_t* Data() const;
        bool IsEnd() const;
        std::uint32_t LeftCapacity() const;
        void Reset();

        std::int32_t ReadSigned32();
        std::uint32_t ReadUnsigned32();
        std::int16_t ReadSigned16();
        std::uint16_t ReadUnsigned16();
        std::int8_t ReadSigned8();
        std::uint8_t ReadUnsigned8();
        std::int64_t ReadSigned64();
        std::uint64_t ReadUnsigned64();
        const String ReadString();
        const String ReadLine();
        const String ReadWord();
        float ReadReal32();
        double ReadReal64();
        void ReadBuffer(void* buffer, std::uint32_t size);
        bool ReadBoolean();

        void WriteSigned64(std::int64_t value);
        void WriteUnsigned64(std::uint64_t value);
        void WriteSigned32(std::int32_t value);
        void WriteUnsigned32(std::uint32_t value);
        void WriteSigned16(std::int16_t value);
        void WriteUnsigned16(std::uint16_t value);
        void WriteSigned8(std::int8_t value);
        void WriteUnsigned8(std::uint8_t value);
        void WriteString(const String& value);
        void WriteReal32(float value);
        void WriteReal64(double value);
        void WriteBoolean(bool value);
        void WriteBuffer(const void* buffer, int size);

		template<class T>
		void WritePod(const T& value) {
			WriteBuffer(&value, sizeof(value));
		}

		template<class T>
		void ReadPod(T& value) {
			ReadBuffer(&value, sizeof(value));
		}

		template<class T, std::size_t N>
		void WriteStdArray(const std::array<T, N>& a) {			
			WriteBuffer(a.data(), sizeof(a[0])*N);
		}

		template<class T, std::size_t N>
		void ReadStdArray(std::array<T, N>& a) {
			ReadBuffer(a.data(), sizeof(a[0])*N);
		}

		template<class T>
		void WriteStdVector(const std::vector<T>& v) {
			WriteUnsigned32((std::uint32_t)v.size());
			if (!v.empty())
				WriteBuffer(v.data(), sizeof(v[0])*v.size());
		}

		template<class T>
		void ReadStdVector(std::vector<T>& v) {
			std::uint32_t count = ReadUnsigned32();
			if (count) {
				v.resize(count);
				ReadBuffer(v.data(), sizeof(v[0])*count);
			}
		}

		template<class T>
		void WriteStdVector(const std::vector<std::vector<T>>& v) {
			std::uint32_t count = (std::uint32_t)v.size();			
			WriteUnsigned32(count);
			if (count) {
				for (const auto& c : v) {
					WriteStdVector(c);
				}
			}
		}

		template<class T>
		void ReadStdVector(std::vector<std::vector<T>>& v) {
			std::uint32_t count = ReadUnsigned32();
			if (count) {
				v.resize(count);				
				for (auto& c : v) {
					ReadStdVector(c);
				}
			}
		}

        void* Release();

        __private::BufferImpl* impl;

    private:
        void Resize(std::uint32_t new_size);
        void WriteData(const void* data, std::uint32_t size);
    };

    template<typename T>
    T* begin(Buffer& buffer) { return reinterpret_cast<T*>(buffer.Data()); }

    template<typename T>
    const T* begin(const Buffer& buffer) { return reinterpret_cast<const T*>(buffer.Data()); }

    template<typename T>
    T* end(Buffer& buffer) { return reinterpret_cast<T*>(buffer.Data())+buffer.GetSize() / sizeof(T); }

    template<typename T>
    const T* end(const Buffer& buffer) { return reinterpret_cast<const T*>(buffer.Data()) + buffer.GetSize() / sizeof(T); }
#endif

}
PUNK_ENGINE_END

#endif	//	_H_PUNK_BUFFER
