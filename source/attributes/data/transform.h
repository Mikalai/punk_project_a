#ifndef _H_PUNK_VIRTUAL_TRANSFORM
#define _H_PUNK_VIRTUAL_TRANSFORM

#include <math/mat4.h>
#include <math/vec3.h>
#include <math/quat.h>
#include <core/object.h>

PUNK_ENGINE_BEGIN
namespace Attributes
{
    class PUNK_ENGINE_API Transform : public Core::Object
	{
	public:

        Transform();
        Transform(const Transform&) = delete;
        Transform& operator = (const Transform&) = delete;
        Transform(const Math::mat4& m);
        virtual ~Transform();
		
		void SetMatrix(const Math::mat4& value);
		const Math::mat4& GetMatrix() const;
		Math::mat4& GetMatrix();

		void SetPosition(const Math::vec3& value);
		const Math::vec3& GetPosition() const;

		void SetRotation(const Math::quat& value);
		const Math::quat& GetRotation() const;

		void SetScale(const Math::vec3& value);
		const Math::vec3& GetScale() const;

	private:
		Math::mat4 m_transform;
		Math::quat m_rotation;
		Math::vec3 m_position;
		Math::vec3 m_scale;		
		mutable bool m_need_update{ true };

	private:        
        PUNK_OBJECT(Transform)
	};    
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_VIRTUAL_TRANSFORM
