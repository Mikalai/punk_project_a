#include "input_component.h"
#include "keyboard.h"
#include "mouse.h"
#include "keymap.h"

PUNK_ENGINE_BEGIN
namespace System
{
    REGISTER_COMPONENT(InputComponent);

#define INPUT_COMPONENT Core::String(L"input")
#define SERVICE_MOUSE Core::String(L"mouse")
#define SERVICE_KEYBOARD Core::String(L"keyboard")
#define SERVICE_KEY_MAP Core::String(L"key_map")

    InputComponent::InputComponent()
        : Core::Component(INPUT_COMPONENT, {SERVICE_MOUSE, SERVICE_KEYBOARD, SERVICE_KEY_MAP}) {}

    Core::Object* InputComponent::OnCreate(const Core::String &name, const Core::String &type, Core::Object **params)
    {
        (void)params;
        Core::Object* o{nullptr};
        if (type == SERVICE_MOUSE)
            o = new Mouse;
        if (type == SERVICE_KEYBOARD)
            o = new Keyboard;
        if (type == SERVICE_KEY_MAP)
            o = new KeyMap;
        if (o)
            o->SetName(name);
        return o;
    }
}
PUNK_ENGINE_END
