#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <system/factory/module.h>
#include <system/logger/module.h>
#include <string/module.h>
#include <core/iserializable.h>
#include <math/matrix.h>
#include <attributes/animation/module.h>
#include <config.h>
#include <string/string.h>
#include "types.h"
#include "ibone.h"
#include "bone.h"

PUNK_ENGINE_BEGIN
namespace Attributes
{
	class AnimationMixer;

	class PUNK_ENGINE_LOCAL Bone : public IBone, public Core::ISerializable
	{
	public:

		Bone() {}

		virtual ~Bone()
		{}
		
		Bone(const Bone&) = delete;
		Bone& operator = (const Bone&) = delete;

		//	IObject
		void QueryInterface(const Core::Guid& type, void** object) {
			if (!object)
				return;
			if (Core::IID_IObject == type) {
				*object = (IBone*)this;
				AddRef();
			}
			else if (IID_IBone == type) {
				*object = (IBone*)this;
				AddRef();
			}
			else if (Core::IID_ISerializable == type) {
				*object = (Core::ISerializable*)this;
				AddRef();
			}
			else {
				*object = nullptr;
			}
		}

		std::uint32_t AddRef() {
			return m_ref_count.fetch_add(1);
		}

		std::uint32_t Release() {
			auto v = m_ref_count.fetch_sub(1) - 1;
			if (!v)
				delete this;
			return v;
		}

		//	IBone
		void SetBoneToArmatureMatrix(const Math::mat4& value) override {
			m_bone_to_armature_matrix = value;
		}

		const Math::mat4& GetBoneToArmatureMatrix() const override {
			return m_bone_to_armature_matrix;
		}

		void SetIndex(std::uint32_t value) override {
			m_index = value;
		}

		std::uint32_t GetIndex() const override {
			return m_index;
		}

		void SetName(const Core::String& value) override {
			m_name = value;
		}

		const Core::String& GetName() const override {
			return m_name;
		}

		void SetLength(float value) override {
			m_length = value;
		}

		float GetLength() const override {
			return m_length;
		}

		void SetParent(std::uint32_t value) override {
			m_parent = value;
		}

		std::uint32_t GetParent() const override {
			return m_parent;
		}

		bool HasParent() const override {
			return m_parent != std::numeric_limits<std::uint32_t>::max();
		}

		void AddChild(std::uint32_t index) override {
			m_children.push_back(index);
		}

		std::uint32_t GetChildrenCount() const override {
			return (std::uint32_t)m_children.size();
		}

		std::uint32_t GetChild(std::uint32_t index) override {
			return m_children.at(index);
		}

		//	ISerializable
		void Serialize(Core::Buffer& buffer) override {
			//	IObject
			buffer.WriteBuffer(CLSID_Bone.ToPointer(), sizeof(CLSID_Bone));
			//	IBone
			buffer.WriteUnsigned32(m_index);
			buffer.WriteUnsigned32(m_parent);
			buffer.WriteBuffer(&m_bone_to_armature_matrix, sizeof(m_bone_to_armature_matrix));
			buffer.WriteString(m_name);
			buffer.WriteReal32(m_length);
			std::uint32_t count = (std::uint32_t)m_children.size();
			buffer.WriteUnsigned32(count);
			buffer.WriteBuffer(m_children.data(), count*sizeof(std::uint32_t));
			//	IAnimated
			auto serializable = Core::QueryInterfacePtr<Core::ISerializable>(m_animation_player, Core::IID_ISerializable);
			bool flag = serializable.get() != nullptr;
			buffer.WriteBoolean(flag);
			if (flag) {				
				serializable->Serialize(buffer);
				buffer.WriteSigned32(m_position_track_index);
				buffer.WriteSigned32(m_rotation_track_index);
				buffer.WriteSigned32(m_scale_track_index);
			}
			count = (std::uint32_t)m_supported_animations.size();
			buffer.WriteUnsigned32(count);
			for (std::uint32_t i = 0; i < count; ++i) {
				buffer.WriteString(m_supported_animations[i]);
			}
		}
		
		void Deserialize(Core::Buffer& buffer) override {
			//	IBone
			m_index = buffer.ReadUnsigned32();
			m_parent = buffer.ReadUnsigned32();
			buffer.ReadBuffer(&m_bone_to_armature_matrix, sizeof(m_bone_to_armature_matrix));
			m_name = buffer.ReadString();
			m_length = buffer.ReadReal32();
			std::uint32_t count = buffer.ReadUnsigned32();
			m_children.resize(count);
			buffer.ReadBuffer(m_children.data(), count*sizeof(std::uint32_t));
			//	IAnimated			
			bool flag = buffer.ReadBoolean();
			if (flag) {
				Core::Guid serializable_guid;
				buffer.ReadBuffer(&serializable_guid, sizeof(serializable_guid));
				auto serializable = System::CreateInstancePtr<Core::ISerializable>(serializable_guid, Core::IID_ISerializable);
				serializable->Deserialize(buffer);
				buffer.WriteSigned32(m_position_track_index);
				buffer.WriteSigned32(m_rotation_track_index);
				buffer.WriteSigned32(m_scale_track_index);
				m_animation_player = Core::QueryInterfacePtr<IAnimationPlayer>(serializable, IID_IAnimationPlayer);
			}
			count = (std::uint32_t)m_supported_animations.size();
			buffer.WriteUnsigned32(count);
			for (std::uint32_t i = 0; i < count; ++i) {
				buffer.WriteString(m_supported_animations[i]);
			}
		}

	private:
		//	IObject
		std::atomic<std::uint32_t> m_ref_count{ 0 };

		//	IBone
		std::uint32_t m_index{ std::numeric_limits<std::uint32_t>::max() };
		std::uint32_t m_parent{ std::numeric_limits<std::uint32_t>::max() };
		Math::mat4 m_bone_to_armature_matrix;
		Core::String m_name;
		float m_length;
		std::vector<std::uint32_t> m_children;		

		//	IAnimated
		Core::Pointer<IAnimationPlayer> m_animation_player{ nullptr, Core::DestroyObject };
		std::int32_t m_position_track_index{ -1 };
		std::int32_t m_rotation_track_index{ -1 };
		std::int32_t m_scale_track_index{ -1 };
		std::vector<Core::String> m_supported_animations;
	};	

	PUNK_REGISTER_CREATOR(CLSID_Bone, (System::CreateInstance<Bone, IBone>));

}
PUNK_ENGINE_END
