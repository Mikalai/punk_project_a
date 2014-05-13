#ifndef _H_IARMATURE_SCHEMA
#define _H_IARMATURE_SCHEMA

#include <cstdint>
#include <config.h>
#include <memory>

PUNK_ENGINE_BEGIN
namespace Core { class String; }
namespace Attributes {
	
	class IBone;

	class IArmatureSchema {
	public:
		virtual IBone* GetBone(std::uint32_t index) = 0;
		virtual const IBone* GetBone(std::uint32_t index) const = 0;
		virtual std::uint32_t GetRootBonesCount() const = 0;
		virtual IBone* GetRootBone(int root_index) = 0;
		virtual const IBone* GetRootBone(int root_index) const = 0;
		virtual int GetBoneIndex(const Core::String& name) = 0;		
		virtual void AddBone(IBone* value) = 0;
	};

	using IArmatureSchemaUniquePtr = std::unique_ptr < IArmatureSchema, void(*)(IArmatureSchema*) > ;

	extern PUNK_ENGINE_API IArmatureSchemaUniquePtr CreateArmatureSchema();
	extern PUNK_ENGINE_API void DestroyArmatureSchema(IArmatureSchema* value);

}
PUNK_ENGINE_END

#endif	//	_H_IARMATURE_SCHEMA