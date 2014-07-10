#ifndef _H_IARMATURE_SCHEMA
#define _H_IARMATURE_SCHEMA

#include <cstdint>
#include <config.h>
#include <memory>
#include <core/iobject.h>

PUNK_ENGINE_BEGIN
namespace Core { class String; }
namespace Attributes {
	
	class IBone;

	DECLARE_PUNK_GUID(IID_IArmatureSchema, "3D4368D1-471B-43FE-BCAF-51E389775B3E");
	DECLARE_PUNK_GUID(CLSID_ArmatureSchema, "40754C77-BDC3-4310-8E51-77F1C8AC8336");

	class IArmatureSchema : public Core::IObject {
	public:
		virtual std::uint32_t GetBonesCount() const = 0;
		virtual Core::Pointer<IBone> GetBone(std::uint32_t index) = 0;
		virtual const Core::Pointer<IBone> GetBone(std::uint32_t index) const = 0;
		virtual std::uint32_t GetRootBonesCount() const = 0;
		virtual Core::Pointer<IBone> GetRootBone(int root_index) = 0;
		virtual const Core::Pointer<IBone> GetRootBone(int root_index) const = 0;
		virtual int GetBoneIndex(const Core::String& name) const = 0;		
		virtual void AddBone(Core::Pointer<IBone> value) = 0;
		virtual std::uint32_t GetSupportedActionsCount() const = 0;
		virtual const Core::String& GetSupportedAction(std::uint32_t index) const = 0;
		virtual void AddSupportedAction(const Core::String& name) = 0;
		virtual void SetName(const Core::String& value) = 0;
		virtual const Core::String& GetName() const = 0;
	};

	using IArmatureSchemaPointer = Core::Pointer < IArmatureSchema > ;
}
PUNK_ENGINE_END

#endif	//	_H_IARMATURE_SCHEMA
