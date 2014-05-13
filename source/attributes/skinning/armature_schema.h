#ifndef _H_ARMATURE_SCHEMA
#define _H_ARMATURE_SCHEMA

#include <config.h>
#include <string/string.h>
#include <core/object.h>
#include "iarmature_schema.h"

PUNK_ENGINE_BEGIN
namespace Attributes {
	class Bone;
	class PUNK_ENGINE_LOCAL ArmatureSchema : public Core::Object, public IArmatureSchema {
	public:
		virtual ~ArmatureSchema();
		IBone* GetBone(std::uint32_t index) override;
		const IBone* GetBone(std::uint32_t index) const override;
		std::uint32_t GetRootBonesCount() const override;
		IBone* GetRootBone(int root_index) override;
		const IBone* GetRootBone(int root_index) const override;
		int GetBoneIndex(const Core::String& name) override;
		void AddBone(IBone* value) override;
		std::uint32_t GetSupportedActionsCount() const override;
		const Core::String& GetSupportedAction(std::uint32_t index) const override;
		void AddSupportedAction(const Core::String& name) override;
	private:
		std::vector<IBone*> m_bones;
		std::vector<std::uint32_t> m_root;
		std::vector<Core::String> m_supported_actions;
		PUNK_OBJECT(ArmatureSchema)
	};
}
PUNK_ENGINE_END

#endif	//	_H_ARMATURE_SCHEMA