#include <algorithm>
#include <stack>
#include <memory>
#include <iostream>
#include <fstream>
#include <vector>
#include <config.h>

#include <system/factory/module.h>
#include <string/module.h>
#include <core/iserializable.h>
#include <math/tuple.h>
#include <math/matrix.h>
#include <string/module.h>

#include <attributes/animation/module.h>

#include "iarmature.h"
#include "ibone.h"
#include "types.h"
#include "iarmature_schema.h"

PUNK_ENGINE_BEGIN
namespace Attributes
{
	class PUNK_ENGINE_LOCAL Armature : public IArmature, public IAnimated, public Core::ISerializable
	{
	public:
		typedef std::vector<Core::String> Actions;
		typedef std::vector<Bone*> Bones;
	public:
		
		Armature() {}
		virtual ~Armature() {}

		Armature(const Armature&) = delete;
		Armature& operator = (const Armature&) = delete;

		//	IObject
		void QueryInterface(const Core::Guid& type, void** object) override {
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
			else if (type == Core::IID_ISerializable) {
				*object = (Core::ISerializable*)this;
				AddRef();
			}
		}

		std::uint32_t AddRef() override {
			return m_ref_count.fetch_add(1);
		}

		std::uint32_t Release() override {
			auto v = m_ref_count.fetch_sub(1) - 1;
			if (!v)
				delete this;
			return v;
		}

		//	IAnimated
		void SetAnimationPlayer(IAnimationPlayer* value) override {
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

		IAnimationPlayer* GetAnimationPlayer() override {
			return m_animation_player.get();
		}

		void AddAnimation(const Core::String& name) override {
			m_supported_animations.push_back(name);
		}

		std::uint32_t GetAnimationsCount() const override {
			return (std::uint32_t)m_supported_animations.size();
		}

		const Core::String& GetAnimation(std::uint32_t index) const override {
			return m_supported_animations.at(index);
		}

		void Update() override {
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

		//	IArmature
		void SetName(const Core::String& value) override {
			m_name = value;
		}

		const Core::String& GetName() const override {
			return m_name;
		}

		const Math::vec3 GetBoneLocalPosition(std::uint32_t index) override {
			return m_bones.at(index).m_child_to_parent.TranslationPart();
		}

		const Math::vec3 GetBoneGlobalPosition(std::uint32_t index) override {
			auto& bone = m_bones.at(index);
			if (bone.m_need_update)
				Update();
			return bone.m_bone_to_armature.TranslationPart();
		}

		const Math::quat GetBoneLocalRotation(std::uint32_t index) override {
			return m_bones.at(index).m_child_to_parent.ToQuaternion();
		}

		const Math::quat GetBoneGlobalRotation(std::uint32_t index) override {
			auto& bone = m_bones.at(index);
			if (bone.m_need_update)
				Update();
			return bone.m_bone_to_armature.ToQuaternion();
		}

		void SetBoneLocalPosition(std::uint32_t index, const Math::vec3& value) override {
		}

		void SetBoneGlobalPosition(std::uint32_t index, const Math::vec3& value) override {
		}

		void SetBoneLocalRotation(std::uint32_t index, const Math::quat& value) override {
		}

		void SetBoneGlobalRotation(std::uint32_t index, const Math::quat& value) override {

		}

		const Core::Pointer<IArmatureSchema> GetSchema() const override {
			return m_schema;
		}

		void SetSchema(Core::Pointer<IArmatureSchema> value) override {
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

		void SetSchemaName(const Core::String& value) override {
			m_schema_name = value;
		}

		const Core::String& GetSchemaName() const override {
			return m_schema_name;
		}

		const Math::mat4 GetBoneGlobalRestMatrix(std::uint32_t index) override {
			return m_bones[index].m_global_matrix;
		}

		const Math::mat4 GetBoneLocalMatrix(std::uint32_t index) override {
			return m_bones[index].m_child_to_parent;
		}

		const Math::mat4 GetBoneGlobalMatrix(std::uint32_t index) override {
			return m_bones[index].m_bone_to_armature;
		}

		//	ISerializable
		void Serialize(Core::Buffer& buffer) override {
			//	IObject
			buffer.WriteBuffer(CLSID_Armature.ToPointer(), sizeof(CLSID_Armature));
			buffer.WriteString(m_name);
			buffer.WriteString(m_schema_name);			
			/*std::uint32_t count = (std::uint32_t)m_bones.size();
			buffer.WriteUnsigned32(count);
			buffer.WriteBuffer(m_bones.data(), m_bones.size()*sizeof(BoneCache));						*/

			//	IAnimated			
			std::uint32_t anim_count = (std::uint32_t)m_supported_animations.size();
			buffer.WriteUnsigned32(anim_count);
			for (std::uint32_t i = 0; i < anim_count; ++i) {
				buffer.WriteString(m_supported_animations[i]);
			}
		}

		void Deserialize(Core::Buffer& buffer) override {
			m_name = buffer.ReadString();
			m_schema_name = buffer.ReadString();
			/*std::uint32_t count = buffer.ReadUnsigned32();
			m_bones.resize(count);
			buffer.ReadBuffer(m_bones.data(), m_bones.size()*sizeof(BoneCache));*/

			//	IAnimated
			std::uint32_t anim_count = buffer.ReadUnsigned32();
			m_supported_animations.resize(anim_count);
			for (std::uint32_t i = 0; i < anim_count; ++i) {
				m_supported_animations[i] = buffer.ReadString();
			}
		}

		private:
		void InternalUpdate() {
			std::stack<Core::Pointer<IBone>> bones;
			for (int i = 0, max_i = m_schema->GetRootBonesCount(); i < max_i; ++i) {
				bones.push(m_schema->GetRootBone(i));
				while (!bones.empty()) {
					auto bone = bones.top();
					bones.pop();

					BoneCache& cache = m_bones.at(bone->GetIndex());

					Math::mat4 local_transform = Math::mat4::CreateTranslate(cache.m_local_position) * Math::mat4::CreateFromQuaternion(cache.m_local_rotation);

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

		const Math::mat4 GetBoneToArmatureMatrix(const IBone* bone) {}

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
	
	PUNK_REGISTER_CREATOR(CLSID_Armature, (System::CreateInstance<Armature, IArmature>));
}
PUNK_ENGINE_END
