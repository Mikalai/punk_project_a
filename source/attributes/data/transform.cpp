#include <system/logger/module.h>
#include "transform.h"

PUNK_ENGINE_BEGIN
namespace Attributes
{
	Core::Rtti TransformType{ "Attributes.Transform", typeid(Transform).hash_code(), { Core::Object::Type() } };

	Core::Rtti* Transform::Type() {
		return &TransformType;
	}

	Transform::Transform(const Math::mat4& m)
	{
		m_transform = m;
	}

    Transform::Transform()
    {}

	Transform::~Transform()
    {}
}
PUNK_ENGINE_END
