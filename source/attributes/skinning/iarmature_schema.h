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

	class IArmatureSchema : public virtual Core::IObject {
	public:
		virtual std::uint32_t GetBonesCount() const = 0;
		virtual IBone* GetBone(std::uint32_t index) = 0;
		virtual const IBone* GetBone(std::uint32_t index) const = 0;
		virtual std::uint32_t GetRootBonesCount() const = 0;
		virtual IBone* GetRootBone(int root_index) = 0;
		virtual const IBone* GetRootBone(int root_index) const = 0;
		virtual int GetBoneIndex(const Core::String& name) = 0;		
		virtual void AddBone(IBone* value) = 0;
		virtual std::uint32_t GetSupportedActionsCount() const = 0;
		virtual const Core::String& GetSupportedAction(std::uint32_t index) const = 0;
		virtual void AddSupportedAction(const Core::String& name) = 0;
	};

	using IArmatureSchemaUniquePtr = Core::UniquePtr < IArmatureSchema > ;
}
PUNK_ENGINE_END

#endif	//	_H_IARMATURE_SCHEMA
