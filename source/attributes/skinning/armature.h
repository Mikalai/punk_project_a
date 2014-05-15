#ifndef _H_PUNK_VIRTUAL_ARMATURE
#define _H_PUNK_VIRTUAL_ARMATURE

#include <memory>
#include <vector>

#include <config.h>
#include <core/object.h>
#include <string/string.h>
#include <math/vec4.h>
#include <math/vec3.h>
#include <math/quat.h>
#include "iarmature.h"
#include "bone.h"
#include "types.h"

PUNK_ENGINE_BEGIN
namespace Attributes {

    class PUNK_ENGINE_LOCAL Armature : public Core::IObject, public IArmature
	{
	public:
        typedef std::vector<Core::String> Actions;
        typedef std::vector<Bone*> Bones;
    public:
		Armature();
        Armature(const Armature&) = delete;
        Armature& operator = (const Armature&) = delete;
        virtual ~Armature();

		const Math::vec3* GetBoneLocalPosition(std::uint32_t index) override;
		const Math::vec3* GetBoneGlobalPosition(std::uint32_t index) override;
		const Math::quat* GetBoneLocalRotation(std::uint32_t index) override;
		const Math::quat* GetBoneGlobalRotation(std::uint32_t index) override;
		void SetBoneLocalPosition(std::uint32_t index, const Math::vec3& value) override;
		void SetBoneGlobalPosition(std::uint32_t index, const Math::vec3& value) override;
		void SetBoneLocalRotation(std::uint32_t index, const Math::quat& value) override;
		void SetBoneGlobalRotation(std::uint32_t index, const Math::quat& value) override;
		void SetSchemaName(const Core::String& name) override;
		const Core::String& GetSchemaName() const override;
		const IArmatureSchema* GetSchema() const override;
		void SetSchema(IArmatureSchema* value) override;
		void SetName(const Core::String& name) override;
		const Core::String& GetName() const override;

	private:
		void Update();

	private:
		struct BoneCache {
			Math::vec3 m_local_position;
			Math::quat m_local_rotation;
			Math::vec3 m_global_position;
			Math::quat m_global_rotation;
			bool m_need_update{ true };
		};

		std::vector<BoneCache> m_bones;
		IArmatureSchema* m_schema{ nullptr };
		Core::String m_name;
		Core::String m_schema_name;

        PUNK_OBJECT_DEFAULT_IMPL(Armature)               
	};
}
PUNK_ENGINE_END

//REGISTER_MANAGER(L"resource.armatures", L"*.armature", System::Environment::Instance()->GetModelFolder(), System::ObjectType::ARMATURE, Attributes, Armature, return, return);

#endif	//	_H_PUNK_VIRTUAL_ARMATURE
