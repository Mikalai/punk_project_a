#ifndef _H_PUNK__TRANSFORM
#define _H_PUNK__TRANSFORM

#include <math/mat4.h>
#include <math/vec3.h>
#include <math/quat.h>
#include "itransform.h"

PUNK_ENGINE_BEGIN
namespace Attributes
{
	class PUNK_ENGINE_LOCAL Transform : public ITransform
	{
	public:

		Transform();
		Transform(const Transform&) = delete;
		Transform& operator = (const Transform&) = delete;
		Transform(const Math::mat4& m);
		virtual ~Transform();

		//	IObject
		void QueryInterface(const Core::Guid& type, void** object) override;

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

	private:
		mutable Math::mat4 m_transform;
		Math::quat m_rotation;
		Math::vec3 m_position;
		Math::vec3 m_scale;
		mutable bool m_need_update{ true };

	private:
		PUNK_OBJECT_DEFAULT_IMPL3(Transform)
	};
}
PUNK_ENGINE_END

#endif	//	_H_PUNK__TRANSFORM
