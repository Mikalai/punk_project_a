#include <system/logger/module.h>
#include "action.h"
#include "animation.h"

PUNK_ENGINE_BEGIN
namespace Attributes
{
    Core::Rtti Action::Type{L"Attributes.Action", typeid(Action).hash_code(), {&Core::Object::Type}};

	Action::Action()
    {}

    Action::~Action()
    {}

    void Action::SetName(const Core::String &value)
    {
        m_name = value;
    }

    const Core::String& Action::GetName() const
    {
        return m_name;
    }
}
PUNK_ENGINE_END
