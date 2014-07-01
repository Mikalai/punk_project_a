#include <algorithm>
#include <stack>
#include <memory>
#include <iostream>
#include <fstream>
#include <vector>
#include <config.h>

#include <system/factory/module.h>
#include <string/string.h>
#include <math/vec4.h>
#include <math/vec3.h>
#include <math/quat.h>
#include <string/module.h>

#include <attributes/animation/module.h>

#include "iarmature.h"
#include "ibone.h"
#include "types.h"
#include "iarmature_schema.h"

PUNK_ENGINE_BEGIN
namespace Attributes
{
	class PUNK_ENGINE_LOCAL Armature : public IArmature, public IAnimated
	{
	public:
		typedef std::vector<Core::String> Actions;
		typedef std::vector<Bone*> Bones;
	public:
		Armature();
		Armature(const Armature&) = delete;
		Armature& operator = (const Armature&) = delete;
		virtual ~Armature();

		//	IObject
		void QueryInterface(const Core::Guid& type, void** object) override;
		std::uint32_t AddRef() override;
		std::uint32_t Release() override;

		//	IAnimated
		void SetAnimationPlayer(IAnimationPlayer* value) override;
		IAnimationPlayer* GetAnimationPlayer() override;
		void AddAnimation(const Core::String& name) override;
		std::uint32_t GetAnimationsCount() const override;
		const Core::String& GetAnimation(std::uint32_t index) const override;
		void Update() override;

		//	IArmature
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

		//	IObject
		std::atomic<std::uint32_t> m_ref_count{ 0 };

		//	IArmature
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

		//	IAnimation
		Core::Pointer<IAnimationPlayer> m_animation_player{ nullptr, Core::DestroyObject };
		struct BoneAnimationCache {
			
		};		
		std::vector<BoneAnimationCache> m_bone_animation_cache;
		std::vector<Core::String> m_supported_animations;
	};

	Armature::Armature()
	{
	}

	Armature::~Armature()
	{
	}

	void Armature::QueryInterface(const Core::Guid& type, void** object) {
		if (!object)
			return;

		*object = nullptr;

		if (type == Core::IID_IObject) {
			*object = (void*)(Core::IObject*)(IArmature*)this;
			AddRef();
			return;
		}
		else if (type == IID_IArmature) {
			*object = (void*)(IArmature*)this;
			AddRef();
			return;
		}
		else if (type == IID_IAnimated) {
			*object = (void*)(IAnimated*)this;
			AddRef();
			return;
		}		
	}

	std::uint32_t Armature::AddRef() {
		return m_ref_count.fetch_add(1);
	}

	std::uint32_t Armature::Release() {
		auto v = m_ref_count.fetch_sub(1) - 1;
		if (!v)
			delete this;
		return v;
	}

	void Armature::SetAnimationPlayer(IAnimationPlayer* value) {
		if (value == m_animation_player.get())
			return;

		value->AddRef();
		m_animation_player.reset(value);

		m_bone_animation_cache.clear();
		m_bone_animation_cache.resize(m_bones.size());
		for (std::uint32_t i = 0, max_i = m_animation_player->GetAnimation()->GetTracksCount(); i < max_i; ++i) {
			auto track = m_animation_player->GetAnimation()->GetTrack(i);
			for (std::uint32_t j = 0, max_j = m_bones.size(); j < max_j; ++j) {
				if (track->GetName() == L"Position") {
					m_position_track_index = i;
				}
				else if (track->GetName() == L"Rotation") {
					m_rotation_track_index = i;
				}
				else if (track->GetName() == L"Scale") {
					m_scale_track_index = i;
				}
			}
		}
	}
	
	IAnimationPlayer* Armature::GetAnimationPlayer() {

	}
	
	void Armature::AddAnimation(const Core::String& name) {

	}
	
	std::uint32_t Armature::GetAnimationsCount() const {

	}
	
	const Core::String& Armature::GetAnimation(std::uint32_t index) const {
	}

	void Armature::Update() {

	}

	void Armature::SetName(const Core::String& value)
	{
		m_name = value;
	}

	const Core::String& Armature::GetName() const
	{
		return m_name;
	}

	const Math::vec3* Armature::GetBoneLocalPosition(std::uint32_t index) {
		return &m_bones.at(index).m_local_position;
	}

	const Math::vec3* Armature::GetBoneGlobalPosition(std::uint32_t index) {
		auto& bone = m_bones.at(index);
		if (bone.m_need_update)
			Update();
		return &bone.m_global_position;
	}

	const Math::quat* Armature::GetBoneLocalRotation(std::uint32_t index) {
		return &m_bones.at(index).m_local_rotation;
	}

	const Math::quat* Armature::GetBoneGlobalRotation(std::uint32_t index) {
		auto& bone = m_bones.at(index);
		if (bone.m_need_update)
			Update();
		return &bone.m_global_rotation;
	}

	void Armature::SetBoneLocalPosition(std::uint32_t index, const Math::vec3& value) {
		m_bones.at(index).m_local_position = value;
		m_bones.at(index).m_need_update = true;
	}

	void Armature::SetBoneGlobalPosition(std::uint32_t index, const Math::vec3& value) {
	}

	void Armature::SetBoneLocalRotation(std::uint32_t index, const Math::quat& value) {
		m_bones.at(index).m_local_rotation = value;
		m_bones.at(index).m_need_update = true;
	}

	void Armature::SetBoneGlobalRotation(std::uint32_t index, const Math::quat& value) {

	}

	const IArmatureSchema* Armature::GetSchema() const {
		return m_schema;
	}

	void Armature::SetSchema(IArmatureSchema* value) {
		m_schema = value;
	}

	void Armature::SetSchemaName(const Core::String& value) {
		m_schema_name = value;
	}

	const Core::String& Armature::GetSchemaName() const {
		return m_schema_name;
	}

	void Armature::Update() {
		std::stack<IBone*> bones;
		for (int i = 0, max_i = m_schema->GetRootBonesCount(); i < max_i; ++i) {
			bones.push(m_schema->GetRootBone(i));
			while (!bones.empty()) {
				IBone* bone = bones.top();
				bones.pop();

				BoneCache& cache = m_bones.at(bone->GetIndex());
				if (cache.m_need_update) {
					if (bone->HasParent()) {
						const BoneCache& parent_cache = m_bones.at(bone->GetParent());
						cache.m_global_position = parent_cache.m_global_position + parent_cache.m_global_rotation.Rotate(cache.m_local_position);
						cache.m_global_rotation = parent_cache.m_global_rotation * cache.m_local_rotation;
					}
					else {
						cache.m_global_position = cache.m_local_position;
						cache.m_global_rotation = cache.m_local_rotation;
					}
					cache.m_need_update = false;
					for (int i = 0, max_i = bone->GetChildrenCount(); i < max_i; ++i) {
						bones.push(m_schema->GetBone(bone->GetChild(i)));
					}
				}
			}
		}
	}

	PUNK_REGISTER_CREATOR(IID_IArmature, (System::CreateInstance<Armature, IArmature>));
}
PUNK_ENGINE_END
