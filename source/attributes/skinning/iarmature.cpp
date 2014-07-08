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
#include <math/mat4.h>
#include <math/matrix_helper.h>
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
		const Math::vec3 GetBoneLocalPosition(std::uint32_t index) override;
		const Math::vec3 GetBoneGlobalPosition(std::uint32_t index) override;
		const Math::quat GetBoneLocalRotation(std::uint32_t index) override;
		const Math::quat GetBoneGlobalRotation(std::uint32_t index) override;
		const Math::mat4 GetBoneLocalMatrix(std::uint32_t index) override;
		const Math::mat4 GetBoneGlobalMatrix(std::uint32_t index) override;
		const Math::mat4 GetBoneGlobalRestMatrix(std::uint32_t index) override;
		void SetBoneLocalPosition(std::uint32_t index, const Math::vec3& value) override;
		void SetBoneGlobalPosition(std::uint32_t index, const Math::vec3& value) override;
		void SetBoneLocalRotation(std::uint32_t index, const Math::quat& value) override;
		void SetBoneGlobalRotation(std::uint32_t index, const Math::quat& value) override;
		void SetSchemaName(const Core::String& name) override;
		const Core::String& GetSchemaName() const override;
		const Core::Pointer<IArmatureSchema> GetSchema() const override;
		void SetSchema(Core::Pointer<IArmatureSchema> value) override;
		void SetName(const Core::String& name) override;
		const Core::String& GetName() const override;

	private:
		void InternalUpdate();
		const Math::mat4 GetBoneToArmatureMatrix(const IBone* bone);

	private:

		//	IObject
		std::atomic<std::uint32_t> m_ref_count{ 0 };

		//	IArmature
		struct BoneCache {
			Math::vec3 m_local_position;
			Math::quat m_local_rotation;
			Math::mat4 m_global_matrix;
			Math::mat4 m_bone_to_armature;
			Math::mat4 m_child_to_parent;
			bool m_need_update{ true };
		};

		std::vector<BoneCache> m_bones;
		Core::Pointer<IArmatureSchema> m_schema{ nullptr, Core::DestroyObject };
		Core::String m_name;
		Core::String m_schema_name;		

		//	IAnimation
		Core::Pointer<IAnimationPlayer> m_animation_player{ nullptr, Core::DestroyObject };		
		std::vector<std::uint32_t> m_position_track_bone;	//	maps track to bone
		std::vector<std::uint32_t> m_rotation_track_bone;	//	maps track to bone
		std::vector<std::uint32_t> m_scale_track_bone;		//	maps track to bone
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

		
		m_position_track_bone.resize(m_animation_player->GetAnimation()->GetTracksCount());
		m_rotation_track_bone.resize(m_animation_player->GetAnimation()->GetTracksCount());
		m_scale_track_bone.resize(m_animation_player->GetAnimation()->GetTracksCount());
		std::fill(m_position_track_bone.begin(), m_position_track_bone.end(), -1);
		std::fill(m_rotation_track_bone.begin(), m_rotation_track_bone.end(), -1);
		std::fill(m_scale_track_bone.begin(), m_scale_track_bone.end(), -1);
		for (std::uint32_t i = 0, max_i = m_animation_player->GetAnimation()->GetTracksCount(); i < max_i; ++i) {
			auto track = m_animation_player->GetAnimation()->GetTrack(i);
			auto list = track->GetName().Split(":");
			auto bone = list[0];
			auto track_type = list[1];
			auto bone_index = GetSchema()->GetBoneIndex(bone);
			for (std::uint32_t j = 0, max_j = (std::uint32_t)m_bones.size(); j < max_j; ++j) {
				if (track_type == L"Position") {
					m_position_track_bone[i] = bone_index;
				}
				else if (track_type == L"Rotation") {
					m_rotation_track_bone[i] = bone_index;
				}
				else if (track->GetName() == L"Scale") {
					m_scale_track_bone[i] = bone_index;
				}
			}
		}
	}
	
	IAnimationPlayer* Armature::GetAnimationPlayer() {
		return m_animation_player.get();
	}
	
	void Armature::AddAnimation(const Core::String& name) {
		m_supported_animations.push_back(name);
	}
	
	std::uint32_t Armature::GetAnimationsCount() const {
		return (std::uint32_t)m_supported_animations.size();
	}
	
	const Core::String& Armature::GetAnimation(std::uint32_t index) const {
		return m_supported_animations.at(index);
	}

	void Armature::Update() {
		if (m_animation_player.get() && m_animation_player->GetAnimation()) {
			for (std::uint32_t track_index = 0, max_i = m_animation_player->GetAnimation()->GetTracksCount(); track_index < max_i; ++track_index) {
				auto track = m_animation_player->GetAnimation()->GetTrack(track_index);
				auto bone_index = m_position_track_bone[track_index];
				if (bone_index != -1) {										
					m_animation_player->GetCurrentValue(track_index, (void*)&m_bones[bone_index].m_local_position, sizeof(m_bones[bone_index].m_local_position));
					m_bones[bone_index].m_need_update = true;					
				}
				bone_index = m_rotation_track_bone[track_index];
				if (bone_index != -1) {
					m_animation_player->GetCurrentValue(track_index, (void*)&m_bones[bone_index].m_local_rotation, sizeof(m_bones[bone_index].m_local_rotation));
					m_bones[bone_index].m_need_update = true;
				}
			}
		}
		InternalUpdate();
	}

	void Armature::SetName(const Core::String& value)
	{
		m_name = value;
	}

	const Core::String& Armature::GetName() const
	{
		return m_name;
	}

	const Math::vec3 Armature::GetBoneLocalPosition(std::uint32_t index) {
		return m_bones.at(index).m_child_to_parent.TranslationPart();
	}

	const Math::vec3 Armature::GetBoneGlobalPosition(std::uint32_t index) {
		auto& bone = m_bones.at(index);
		if (bone.m_need_update)
			Update();
		return bone.m_bone_to_armature.TranslationPart();
	}

	const Math::quat Armature::GetBoneLocalRotation(std::uint32_t index) {
		return Math::quat::CreateFromMatrix4x4(m_bones.at(index).m_child_to_parent);
	}

	const Math::quat Armature::GetBoneGlobalRotation(std::uint32_t index) {
		auto& bone = m_bones.at(index);
		if (bone.m_need_update)
			Update();
		return Math::quat::CreateFromMatrix4x4(bone.m_bone_to_armature);
	}

	void Armature::SetBoneLocalPosition(std::uint32_t index, const Math::vec3& value) {
	}

	void Armature::SetBoneGlobalPosition(std::uint32_t index, const Math::vec3& value) {
	}

	void Armature::SetBoneLocalRotation(std::uint32_t index, const Math::quat& value) {
	}

	void Armature::SetBoneGlobalRotation(std::uint32_t index, const Math::quat& value) {

	}

	const Core::Pointer<IArmatureSchema> Armature::GetSchema() const {
		return m_schema;
	}

	void Armature::SetSchema(Core::Pointer<IArmatureSchema> value) {
		m_schema = value;
		m_supported_animations.clear();
		if (m_schema) {
			for (std::uint32_t i = 0, max_i = value->GetSupportedActionsCount(); i < max_i; ++i) {
				m_supported_animations.push_back(value->GetSupportedAction(i));
			}
			//	allocate bones cache
			m_bones.resize(m_schema->GetBonesCount());
		}
	}

	void Armature::SetSchemaName(const Core::String& value) {
		m_schema_name = value;
	}

	const Core::String& Armature::GetSchemaName() const {
		return m_schema_name;
	}

	void Armature::InternalUpdate() {
		std::stack<IBone*> bones;
		for (int i = 0, max_i = m_schema->GetRootBonesCount(); i < max_i; ++i) {
			bones.push(m_schema->GetRootBone(i));
			while (!bones.empty()) {
				IBone* bone = bones.top();
				bones.pop();

				BoneCache& cache = m_bones.at(bone->GetIndex());

				Math::mat4 local_transform = Math::CreateTranslate(cache.m_local_position) * cache.m_local_rotation.ToMatrix4x4();

				if (cache.m_need_update) {
					if (bone->HasParent()) {
						const BoneCache& parent_cache = m_bones.at(bone->GetParent());
						cache.m_global_matrix = bone->GetBoneToArmatureMatrix();
						cache.m_child_to_parent = parent_cache.m_child_to_parent * parent_cache.m_global_matrix.Inversed() * bone->GetBoneToArmatureMatrix() * local_transform;
						cache.m_bone_to_armature = parent_cache.m_bone_to_armature * bone->GetBoneToArmatureMatrix() * local_transform * bone->GetBoneToArmatureMatrix().Inversed();
					}
					else {
						cache.m_global_matrix = bone->GetBoneToArmatureMatrix();
						cache.m_child_to_parent = bone->GetBoneToArmatureMatrix() * local_transform;
						cache.m_bone_to_armature = bone->GetBoneToArmatureMatrix() * local_transform * bone->GetBoneToArmatureMatrix().Inversed();
					}
					cache.m_need_update = false;
					for (int i = 0, max_i = bone->GetChildrenCount(); i < max_i; ++i) {
						bones.push(m_schema->GetBone(bone->GetChild(i)));
					}
				}
			}
		}
	}	

	const Math::mat4 Armature::GetBoneGlobalRestMatrix(std::uint32_t index) {
		return m_bones[index].m_global_matrix;
	}

	const Math::mat4 Armature::GetBoneLocalMatrix(std::uint32_t index) {
		return m_bones[index].m_child_to_parent;
	}

	const Math::mat4 Armature::GetBoneGlobalMatrix(std::uint32_t index) {		
		return m_bones[index].m_bone_to_armature;
	}

	PUNK_REGISTER_CREATOR(IID_IArmature, (System::CreateInstance<Armature, IArmature>));
}
PUNK_ENGINE_END
