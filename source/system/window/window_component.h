#ifndef WINDOW_COMPONENT_H
#define WINDOW_COMPONENT_H

#include "core/component/module.h"
#include "system/window/window_description.h"

PUNK_ENGINE_BEGIN
namespace System
{
    class Window;
    class PUNK_ENGINE_LOCAL WindowComponent : public Core::Component
    {
    public:
        WindowComponent();

    protected:
        Core::Object* OnCreate(const Core::String &, const Core::String &, Core::Object **) override;

        WindowDesc m_desc;  // TODO: Should be loaded from file at start up        
    };
}
PUNK_ENGINE_END

#endif // WINDOW_COMPONENT_H
