#ifndef _H_IBONE
#define _H_IBONE

#include <config.h>
#include <cstdint>

PUNK_ENGINE_BEGIN
namespace Core {
	class String;
}
namespace Math {
	class mat4;
}
namespace Attributes {
	class IBone {
	public:
		virtual void SetIndex(std::uint32_t value) = 0;
		virtual std::uint32_t GetIndex() const = 0;
		virtual void SetName(const Core::String& value) = 0;
		virtual const Core::String& GetName() const = 0;
		virtual void SetLength(float value) = 0;
		virtual float GetLength() const = 0;
		virtual void SetRestMatrix(const Math::mat4& value) = 0;
		virtual const Math::mat4& GetRestMatrix() const = 0;
		virtual void SetParent(std::uint32_t value) = 0;
		virtual std::uint32_t GetParent() const = 0;
	};
}
PUNK_ENGINE_END

#endif	//	_H_IBONE