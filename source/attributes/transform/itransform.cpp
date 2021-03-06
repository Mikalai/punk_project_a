#include <math/matrix.h>
#include <math/tuple.h>
#include <string/buffer.h>
#include <core/iserializable.h>
#include <core/iclonable.h>
#include <core/value_monitor.h>
#include <system/factory/module.h>
#include <system/logger/module.h>
#include <system/dbg/module.h>
#include <system/dbg/isupport_debugger_template.h>
#include <attributes/animation/module.h>
#include <attributes/animation/module.h>
#include <tools/editor/editor_interface.h>
#include <attributes/collection/icollection_impl.h>
#include "itransform.h"

PUNK_ENGINE_BEGIN
namespace Attributes {

	class PUNK_ENGINE_LOCAL Transform
		: public ITransform
		, public IAnimated
		, public Core::ISerializable
		, public Core::IClonable
		, public Tools::IEditableElement
		, public ICollection
		, public System::ISupportDebugImpl < Transform > {
	public:

		Transform(const Math::mat4& m) {
			m_transform.Set(m);
			Subscribe();
		}

		Transform()
		{
			Subscribe();
		}

		void Subscribe() {
			m_position.SubscribeOnValueChanged({ new Core::Action < Transform, const Math::vec3& > { this, &Transform::SetPosition }, Core::DestroyObject });
			m_rotation.SubscribeOnValueChanged({ new Core::Action < Transform, const Math::quat& >{ this, &Transform::SetRotation }, Core::DestroyObject });
			m_scale.SubscribeOnValueChanged({ new Core::Action < Transform, const Math::vec3& >{ this, &Transform::SetScale }, Core::DestroyObject });
			m_transform.SubscribeOnValueChanged({ new Core::Action < Transform, const Math::mat4&>{ this, &Transform::SetMatrix}, Core::DestroyObject });
		}

		virtual ~Transform()
		{
		}

		Transform(const Transform&) = delete;
		Transform& operator = (const Transform&) = delete;

		//	IObject
		void QueryInterface(const Core::Guid& type, void** object) override {
			if (!object)
				return;

			if (type == Core::IID_IObject) {
				*object = (Core::IObject*)(ITransform*)this;
				AddRef();
			}
			else if (type == IID_ITransform) {
				*object = (void*)(ITransform*)this;
				AddRef();
			}
			else if (type == IID_IAnimated) {
				*object = (void*)(IAnimated*)this;
				AddRef();
			}
			else if (type == Core::IID_ISerializable) {
				*object = (void*)(Core::ISerializable*)this;
				AddRef();
			}
			else if (type == Tools::IID_IEditableElement) {
				*object = (void*)(Tools::IEditableElement*)this;
				AddRef();
			}
			else if (type == Core::IID_IClonable) {
				*object = (void*)(Core::IClonable*)this;
				AddRef();
			}
			else if (type == System::IID_ISupportDebugger) {
				*object = (void*)(System::ISupportDebug*)this;
				AddRef();
			}
			else if (type == IID_ICollection) {
				*object = (void*)(ICollection*)this;
				AddRef();
			}
			else
				*object = nullptr;
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

		void SetMatrix(const Math::mat4& value) override {
			m_transform.Set(value);
			Math::vec3 pos, scale;
			Math::quat rot;
			m_transform.Get().Decompose(pos, rot, scale);
			m_position.Set(pos);
			m_rotation.Set(rot);
			m_scale.Set(scale);
			m_need_update = false;
		}

		const Math::mat4& GetMatrix() const override {
			if (m_need_update) {				
				m_transform.Set(Math::mat4::CreatePositionRotationScaleMatrix(m_position.Get(), m_rotation.Get(), m_scale.Get()));
				m_need_update = false;
			}
			return m_transform;
		}

		Math::mat4& GetMatrix() override {
			return const_cast<Math::mat4&>(static_cast<const Transform&>(*this).GetMatrix());
		}

		void SetPosition(const Math::vec3& value) override {
			m_position.Set(value);
			m_need_update = true;
			GetMatrix();
		}

		const Math::vec3& GetPosition() const override {
			return m_position.Get();
		}

		void SetRotation(const Math::quat& value) override {
			m_rotation.Set(value);
			m_need_update = true;
			GetMatrix();
		}

		const Math::quat& GetRotation() const override {
			return m_rotation.Get();
		}

		void SetScale(const Math::vec3& value) override {
			m_scale.Set(value);			
			m_need_update = true;
			GetMatrix();
		}

		const Math::vec3& GetScale() const override {
			return m_scale.Get();
		}

		//	IAnimated
		void SetAnimationPlayer(Core::Pointer<IAnimationPlayer> value) override {
			if (value == m_animation_player)
				return;

			m_animation_player = value;

			m_position_track_index = -1;
			m_scale_track_index = -1;
			m_rotation_track_index = -1;
			for (std::uint32_t i = 0, max_i = m_animation_player->GetAnimation()->GetTracksCount(); i < max_i; ++i) {
				auto track = m_animation_player->GetAnimation()->GetTrack(i);
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

		IAnimationPlayer* GetAnimationPlayer() override {
			return m_animation_player.get();
		}

		void Update() override {
			if (m_animation_player.get() && m_animation_player->GetAnimation()) {
				for (std::uint32_t track_index = 0, max_i = m_animation_player->GetAnimation()->GetTracksCount(); track_index < max_i; ++track_index) {
					auto track = m_animation_player->GetAnimation()->GetTrack(track_index);
					if (track_index == m_position_track_index) {
						m_animation_player->GetCurrentValue(track_index, (void*)&m_position, sizeof(m_position));
						m_need_update = true;
					}
					else if (track_index == m_rotation_track_index) {
						m_animation_player->GetCurrentValue(track_index, (void*)&m_rotation, sizeof(m_rotation));
						m_need_update = true;
					}
					else if (track_index == m_scale_track_index) {
						m_animation_player->GetCurrentValue(track_index, (void*)&m_scale, sizeof(m_scale));
						m_need_update = true;
					}
				}
			}
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

		//	ISerializable
		void Serialize(Core::Buffer& buffer) override {
			buffer.WriteBuffer(CLSID_Transform.ToPointer(), sizeof(CLSID_Transform));
			//	Save ITransform
			buffer.WriteBuffer(&m_rotation, sizeof(m_rotation));
			buffer.WriteBuffer(&m_position, sizeof(m_position));
			buffer.WriteBuffer(&m_scale, sizeof(m_scale));
			//	Save IAnimated			
			std::uint32_t anim_count = (std::uint32_t)m_supported_animations.size();
			buffer.WriteUnsigned32(anim_count);
			for (std::uint32_t i = 0; i < anim_count; ++i) {
				buffer.WriteString(m_supported_animations[i]);
			}
		}

		void Deserialize(Core::Buffer& buffer) override {
			//	Save ITransform
			buffer.ReadBuffer(&m_rotation, sizeof(m_rotation));
			buffer.ReadBuffer(&m_position, sizeof(m_position));
			buffer.ReadBuffer(&m_scale, sizeof(m_scale));
			//	Save IAnimated			
			std::uint32_t anim_count = buffer.ReadUnsigned32();
			m_supported_animations.resize(anim_count);
			for (std::uint32_t i = 0; i < anim_count; ++i) {
				m_supported_animations[i] = buffer.ReadString();
			}
		}

		//	IClonable
		Core::Pointer<IClonable> Clone() const override {
			auto clone = std::unique_ptr < Transform > { new Transform };
			clone->SetMatrix(GetMatrix());

			{
				auto tmp = Core::QueryInterfacePtr<Core::IClonable>(m_animation_player, Core::IID_IClonable);
				if (tmp) {
					auto o = tmp->Clone();
					auto player = Core::QueryInterfacePtr<IAnimationPlayer>(o, IID_IAnimationPlayer);
					clone->SetAnimationPlayer(player);
				}
			}
			for (std::uint32_t i = 0, max_i = GetAnimationsCount(); i < max_i; ++i) {
				clone->AddAnimation(GetAnimation(i));
			}
			return Core::Pointer < IClonable > {clone.release(), Core::DestroyObject};
		}

		//	IEditableElement
		void AddToPanel(Tools::IEditorParametersPanel* panel) override {
			panel->AddVec3FloatEditor("Position:", &m_position);
			panel->AddQuatFloatEditor("Rotation:", &m_rotation);
			panel->AddVec3FloatEditor("Scale:", &m_scale);
			panel->AddMat4FloatEditor("Transform:", &m_transform);
		}

		//	ICollection
		void Add(Core::Pointer<Core::IObject> value) override {
			m_children.Add(value);
		}

		void Remove(Core::Pointer<Core::IObject> value) override {
			m_children.Remove(value);
		}

		std::uint32_t Size() const override {
			return m_children.Size();
		}

		const Core::Pointer<Core::IObject> GetItem(std::uint32_t index) const override {
			return m_children.GetItem(index);
		}

		Core::Pointer<Core::IObject> GetItem(std::uint32_t index) override {
			return m_children.GetItem(index);
		}

	private:
		//	IObject
		std::atomic<std::uint32_t> m_ref_count{ 0 };

		//	ITransform
		mutable Core::ValueMonitor<Math::mat4> m_transform;
		Core::ValueMonitor<Math::quat> m_rotation{ { 0, 0, 0, 0 } };
		Core::ValueMonitor<Math::vec3> m_position{ { 0, 0, 0 } };
		Core::ValueMonitor<Math::vec3> m_scale{ { 1, 1, 1 } };
		mutable bool m_need_update{ true };

		//	IAnimated
		Core::Pointer<IAnimationPlayer> m_animation_player{ nullptr, Core::DestroyObject };
		std::int32_t m_position_track_index{ -1 };
		std::int32_t m_rotation_track_index{ -1 };
		std::int32_t m_scale_track_index{ -1 };
		std::vector<Core::String> m_supported_animations;

		//	ICollection
		Collection<Core::IObject> m_children;
	};

	PUNK_REGISTER_CREATOR(CLSID_Transform, (System::CreateInstance<Transform, ITransform>));
}
PUNK_ENGINE_END
