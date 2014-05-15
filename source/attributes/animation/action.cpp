#include <system/logger/module.h>
#include "action.h"
#include "animation.h"

PUNK_ENGINE_BEGIN
namespace Attributes
{
	Action::Action()
		: m_container{ this, Core::GetRootObject() }
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
