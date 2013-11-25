#include "system/window/module.h"
#include "window_component.h"

PUNK_ENGINE_BEGIN
namespace System
{
    REGISTER_COMPONENT(WindowComponent);

#define WINDOW_SERVICE Core::String(L"window")
#define WINDOW_COMPONENT Core::String(L"window")

    WindowComponent::WindowComponent()
        : Core::Component(WINDOW_COMPONENT, {WINDOW_SERVICE}) {}

    Core::Object* WindowComponent::OnCreate(const Core::String &name, const Core::String &type, Core::Object **)
    {        
        if (type == WINDOW_SERVICE)
        {
            m_desc.m_name = name;
            Core::Object* o = CreateRootWindow(m_desc);
            if (o)
                o->SetName(name);
            return o;
        }
        return nullptr;
    }
}
PUNK_ENGINE_END
