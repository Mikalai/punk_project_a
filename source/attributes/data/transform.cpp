#include <system/logger/module.h>
#include "transform.h"

PUNK_ENGINE_BEGIN
namespace Attributes
{
    Core::Rtti Transform::Type{"Attributes.Transform",
                               typeid(Transform).hash_code(),
        {&Core::Object::Type}};

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
