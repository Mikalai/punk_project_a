#ifndef _H_PUNK_BINARY_FILE
#define _H_PUNK_BINARY_FILE

#include <iosfwd>
#include <config.h>

PUNK_ENGINE_BEGIN
namespace Core {
    class String;
    class Buffer;
}
namespace System {

    class PUNK_ENGINE_API BinaryFile {
	public:
        static bool Load(const Core::String& filename, Core::Buffer& buffer);
        static bool Load(std::istream& stream, Core::Buffer& buffer);
        static bool Save(const Core::String& filename, const Core::Buffer& buffer);
        static bool Append(const Core::String& filename, const Core::Buffer& buffer);
        static bool Truncate(const Core::String& filename);
	};
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_BINARY_FILE
