#ifndef _H_IBONE
#define _H_IBONE

#include <config.h>
#include <cstdint>
#include <memory>
#include <core/iobject.h>
#include <math/mat4.h>

PUNK_ENGINE_BEGIN
namespace Core {
	class String;
}
namespace Attributes {

	DECLARE_PUNK_GUID(IID_IBone, "58B3E09C-8DC9-4A13-BC04-A76D74DF5C65");
	DECLARE_PUNK_GUID(CLSID_Bone, "3E5A235D-1FBA-4631-90CA-ED99EC688E1D");

	class IBone : public Core::IObject {
	public:
		virtual void SetIndex(std::uint32_t value) = 0;
		virtual std::uint32_t GetIndex() const = 0;
		virtual void SetName(const Core::String& value) = 0;
		virtual const Core::String& GetName() const = 0;
		virtual void SetLength(float value) = 0;
		virtual float GetLength() const = 0;
		virtual void SetBoneToArmatureMatrix(const Math::mat4& value) = 0;
		virtual const Math::mat4& GetBoneToArmatureMatrix() const = 0;		
		virtual void SetParent(std::uint32_t value) = 0;
		virtual std::uint32_t GetParent() const = 0;
		virtual bool HasParent() const = 0;
		virtual void AddChild(std::uint32_t index) = 0;
		virtual std::uint32_t GetChildrenCount() const = 0;
		virtual std::uint32_t GetChild(std::uint32_t index) = 0;
	};

	using IBonePointer = Core::Pointer < IBone > ;
}
PUNK_ENGINE_END

#endif	//	_H_IBONE