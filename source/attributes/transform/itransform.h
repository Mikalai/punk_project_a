#ifndef _H_PUNK_VIRTUAL_ITRANSFORM
#define _H_PUNK_VIRTUAL_ITRANSFORM

#include <math/mat4.h>
#include <math/vec3.h>
#include <math/quat.h>
#include <core/iobject.h>

PUNK_ENGINE_BEGIN
namespace Attributes
{
	DECLARE_PUNK_GUID(IID_ITransform, "D5E28CA8-6751-46C3-8AE3-707FCFBF57A3");
	DECLARE_PUNK_GUID(CLSID_Transform, "2410BE45-F38B-48D1-A8BA-9AC99406B2F8");

    class ITransform : public Core::IObject {
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
