#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <system/factory/module.h>
#include <system/logger/module.h>
#include <string/module.h>
#include <math/quat.h>
#include <math/mat4.h>
#include <math/vec3.h>
#include <math/helper.h>
#include <attributes/animation/module.h>
#include <config.h>
#include <math/mat4.h>
#include <string/string.h>
#include "types.h"
#include "ibone.h"
#include "bone.h"

PUNK_ENGINE_BEGIN
namespace Attributes
{
	class AnimationMixer;

	class PUNK_ENGINE_LOCAL Bone : public IBone, IAnimated
	{
	public:

		Bone();
		Bone(const Bone&) = delete;
		Bone& operator = (const Bone&) = delete;
		virtual ~Bone();

		//	IObject
		void QueryInterface(const Core::Guid& type, void** object) override;
		std::uint32_t AddRef() override;
		std::uint32_t Release() override;

		//	IBone
		void SetIndex(std::uint32_t value) override;
		std::uint32_t GetIndex() const override;
		void SetName(const Core::String& value) override;
		const Core::String& GetName() const override;
		void SetLength(float value) override;
		float GetLength() const override;
		void SetRestPosition(const Math::vec3& value) override;
		void SetRestRotation(const Math::quat& value) override;
		const Math::vec3& GetRestPosition() const override;
		const Math::quat& GetRestRotation() const override;
		void SetParent(std::uint32_t value) override;
		std::uint32_t GetParent() const override;
		bool HasParent() const override;
		void AddChild(std::uint32_t index) override;
		std::uint32_t GetChildrenCount() const override;
		std::uint32_t GetChild(std::uint32_t index) override;

	private:
		//	IObject
		std::atomic<std::uint32_t> m_ref_count{ 0 };

		//	IBone
		std::uint32_t m_index{ std::numeric_limits<std::uint32_t>::infinity() };
		std::uint32_t m_parent{ std::numeric_limits<std::uint32_t>::infinity() };
		Math::vec3 m_rest_position;
		Math::quat m_rest_rotation;
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

	Bone::Bone() {}

	Bone::~Bone()
	{}

	void Bone::QueryInterface(const Core::Guid& type, void** object) {
		Core::QueryInterface(this, type, object, { Core::IID_IObject, IID_IBone});
	}

	std::uint32_t Bone::AddRef() {
		return m_ref_count.fetch_add(1);
	}

	std::uint32_t Bone::Release() {
		auto v = m_ref_count.fetch_sub(1) - 1;
		if (!v)
			delete this;
		return v;
	}

	void Bone::SetRestPosition(const Math::vec3& value) {
		m_rest_position = value;
	}

	void Bone::SetRestRotation(const Math::quat& value) {
		m_rest_rotation = value;
	}

	const Math::vec3& Bone::GetRestPosition() const {
		return m_rest_position;
	}

	const Math::quat& Bone::GetRestRotation() const {
		return m_rest_rotation;
	}

	void Bone::SetIndex(std::uint32_t value) {
		m_index = value;
	}

	std::uint32_t Bone::GetIndex() const {
		return m_index;
	}

	void Bone::SetName(const Core::String& value) {
		m_name = value;
	}

	const Core::String& Bone::GetName() const {
		return m_name;
	}

	void Bone::SetLength(float value) {
		m_length = value;
	}

	float Bone::GetLength() const {
		return m_length;
	}	

	void Bone::SetParent(std::uint32_t value) {
		m_parent = value;
	}

	std::uint32_t Bone::GetParent() const {
		return m_parent;
	}

	bool Bone::HasParent() const {
		return m_parent != std::numeric_limits<std::uint32_t>::infinity();
	}

	void Bone::AddChild(std::uint32_t index) {
		m_children.push_back(index);
	}

	std::uint32_t Bone::GetChildrenCount() const {
		return (std::uint32_t)m_children.size();
	}

	std::uint32_t Bone::GetChild(std::uint32_t index) {
		return m_children.at(index);
	}

	PUNK_REGISTER_CREATOR(IID_IBone, (System::CreateInstance<Bone, IBone>));

}
PUNK_ENGINE_END
