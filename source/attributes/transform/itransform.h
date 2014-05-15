#ifndef _H_PUNK_VIRTUAL_ITRANSFORM
#define _H_PUNK_VIRTUAL_ITRANSFORM

#include <math/mat4.h>
#include <math/vec3.h>
#include <math/quat.h>
#include <core/object.h>

PUNK_ENGINE_BEGIN
namespace Attributes
{
    class ITransform : public virtual Core::IObject {
	public:
		virtual void SetMatrix(const Math::mat4& value) = 0;
		virtual const Math::mat4& GetMatrix() const = 0;
		virtual Math::mat4& GetMatrix() = 0;
		virtual void SetPosition(const Math::vec3& value) = 0;
		virtual const Math::vec3& GetPosition() const = 0;
		virtual void SetRotation(const Math::quat& value) = 0;
		virtual const Math::quat& GetRotation() const = 0;
		virtual void SetScale(const Math::vec3& value) = 0;
		virtual const Math::vec3& GetScale() const = 0;
	};    
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_VIRTUAL_TRANSFORM
