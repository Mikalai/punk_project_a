#ifndef _H_PUNK__TRANSFORM
#define _H_PUNK__TRANSFORM

#include <math/mat4.h>
#include <math/vec3.h>
#include <math/quat.h>
#include <attributes/animation/ianimated.h>
#include "itransform.h"

PUNK_ENGINE_BEGIN
namespace Attributes
{
	class PUNK_ENGINE_LOCAL Transform : public ITransform, public IAnimated
	{
	public:

		Transform();
		Transform(const Transform&) = delete;
		Transform& operator = (const Transform&) = delete;
		Transform(const Math::mat4& m);
		virtual ~Transform();

		//	IObject
		void QueryInterface(const Core::Guid& type, void** object) override;
		std::uint32_t AddRef() override;		
		std::uint32_t Release() override;

		//	ITransform
		void SetMatrix(const Math::mat4& value) override;
		const Math::mat4& GetMatrix() const override;
		Math::mat4& GetMatrix() override;
		void SetPosition(const Math::vec3& value) override;
		const Math::vec3& GetPosition() const override;
		void SetRotation(const Math::quat& value) override;
		const Math::quat& GetRotation() const override;
		void SetScale(const Math::vec3& value) override;
		const Math::vec3& GetScale() const override;

		//	IAnimated
		void SetAnimationData(IAnimation* value) override;
		IAnimation* GetAnimationData() override;
		void AddAnimation(const Core::String& name) override;
		std::uint32_t GetAnimationsCount() const override;
		const Core::String& GetAnimation(std::uint32_t index) const override;
		void Advance(std::int32_t track_index, std::int32_t frame, void* data, std::int32_t value) override;

	private:
		Core::UniquePtr<IAnimation> m_animation_data{ nullptr, Core::DestroyObject };
		std::int32_t m_position_track_index{ -1 };
		std::int32_t m_rotation_track_index{ -1 };
		std::int32_t m_scale_track_index{ -1 };
		std::atomic<std::uint32_t> m_ref_count{ 1 };
		std::vector<Core::String> m_supported_animations;
		mutable Math::mat4 m_transform;
		Math::quat m_rotation;
		Math::vec3 m_position;
		Math::vec3 m_scale;
		mutable bool m_need_update{ true };
	};
}
PUNK_ENGINE_END

#endif	//	_H_PUNK__TRANSFORM
