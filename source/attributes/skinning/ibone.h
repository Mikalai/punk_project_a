#ifndef _H_IBONE
#define _H_IBONE

#include <config.h>
#include <cstdint>
#include <memory>

PUNK_ENGINE_BEGIN
namespace Core {
	class String;
}
namespace Math {
	class vec3;
	class quat;
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
		virtual void SetRestPosition(const Math::vec3& value) = 0;
		virtual void SetRestRotation(const Math::quat& value) = 0;
		virtual const Math::vec3& GetRestPosition() const = 0;
		virtual const Math::quat& GetRestRotation() const = 0;
		virtual void SetParent(std::uint32_t value) = 0;
		virtual std::uint32_t GetParent() const = 0;
		virtual bool HasParent() const = 0;
		virtual void AddChild(std::uint32_t index) = 0;
		virtual std::uint32_t GetChildrenCount() const = 0;
		virtual std::uint32_t GetChild(std::uint32_t index) = 0;
	};

	using IBoneUniquePtr = std::unique_ptr < IBone, void(*)(IBone*) > ;
	extern PUNK_ENGINE_API IBoneUniquePtr CreateBone();
	extern PUNK_ENGINE_API void DestroyBone(IBone* value);
}
PUNK_ENGINE_END

#endif	//	_H_IBONE