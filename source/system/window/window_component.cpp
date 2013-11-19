#include "system/window/module.h"
#include "window_component.h"

namespace System
{
#ifdef USE_WINDOW_MODULE
    REGISTER_COMPONENT(WindowComponent, new WindowComponent, {""})
#endif

#define WINDOW_SERVICE string(L"window")
#define WINDOW_COMPONENT string(L"window")

    WindowComponent::WindowComponent()
    {
    }

    void WindowComponent::OnInitialize()
    {
        Create();
    }

    void WindowComponent::OnDetach()
    {
        Clear();
    }

    WindowComponent::~WindowComponent()
    {
        Clear();
    }

    Object* WindowComponent::OnGetService(const string &name)
    {
        if (name == WINDOW_SERVICE)
            return m_window;
        return nullptr;
    }

    const string WindowComponent::GetName() const
    {
        return WINDOW_COMPONENT;
    }

    const StringList WindowComponent::GetServicesList() const
    {
        StringList list;
        list.push_back(WINDOW_SERVICE);
        return list;
    }

    void WindowComponent::Clear()
    {
        delete m_window;
        m_window = nullptr;
    }

    void WindowComponent::Create()
    {
        m_window = CreateRootWindow(m_desc);
    }
}
