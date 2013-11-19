#include "input_component.h"
#include "keyboard.h"
#include "mouse.h"
#include "keymap.h"

namespace System
{
    REGISTER_COMPONENT(InputComponent, new InputComponent, {"window"})

#define INPUT_COMPONENT string(L"input")
#define SERVICE_MOUSE string(L"mouse")
#define SERVICE_KEYBOARD string(L"keyboard")
#define SERVICE_KEY_MAP string(L"key_map")

    InputComponent::InputComponent()
    {
        SetName(INPUT_COMPONENT);
        AddService(SERVICE_MOUSE);
        AddService(SERVICE_KEYBOARD);
        AddService(SERVICE_KEY_MAP);
    }

    void InputComponent::Clear()
    {
        delete m_mouse;
        m_mouse = nullptr;
        delete m_keyboard;
        m_keyboard = nullptr;
        delete m_key_map;
        m_key_map = nullptr;
    }

    void InputComponent::Create()
    {
        m_mouse = new Mouse;
        m_keyboard = new Keyboard;
        m_key_map = new KeyMap;
    }

    void InputComponent::OnInitialize()
    {
        Create();
    }

    void InputComponent::OnDetach()
    {
        Clear();
    }

    Object* InputComponent::OnGetService(const string &name)
    {
        if (name == SERVICE_MOUSE)
            return m_mouse;
        if (name == SERVICE_KEYBOARD)
            return m_keyboard;
        if (name == SERVICE_KEY_MAP)
            return m_key_map;
        return nullptr;
    }
}
