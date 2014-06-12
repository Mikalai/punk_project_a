#ifndef _H_IBONE
#define _H_IBONE

#include <config.h>
#include <cstdint>
#include <memory>
#include <core/iobject.h>

PUNK_ENGINE_BEGIN
namespace Core {
	class String;
}
namespace Math {
	class vec3;
	class quat;
}
namespace Attributes {

	DECLARE_PUNK_GUID(IID_IBone, "58B3E09C-8DC9-4A13-BC04-A76D74DF5C65");

	class IBone : public Core::IObject {
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

	using IBoneUniquePtr = Core::UniquePtr < IBone > ;
}
PUNK_ENGINE_END

#endif	//	_H_IBONE