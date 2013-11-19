#ifdef USE_SYSTEM_MODULE

#include <iostream>
#include <algorithm>
#include "system/errors/module.h"
#include "component.h"
#include "components_pool_impl.h"

namespace System
{
    ComponentsPoolImpl::~ComponentsPoolImpl()
    {
        while (!m_components.empty())
        {
            std::wcout << L"Memory leak detected: " << m_components.back()->GetName() << std::endl;
            delete m_components.back();
            m_components.pop_back();
        }
    }

    Component* ComponentsPoolImpl::FindComponent(const string &name)
    {
        auto it = std::find_if(m_components.begin(), m_components.end(),
                            [&name](Component* c) -> bool { return c->GetName() == name; }
        );
        if (it == m_components.end())
            return nullptr;
        return *it;
    }

    void ComponentsPoolImpl::Initialize()
    {
        for (auto c : m_components)
            c->Initialize();
        std::cout << "Components list: " << std::endl;
        for (auto c : m_components)
        {
            std::wcout << c->GetName() << std::endl;
        }
    }

    void ComponentsPoolImpl::Clear()
    {
        auto components = m_components;
        for (auto c : components)
            c->Detach();
    }

    void ComponentsPoolImpl::RegisterComponent(const string &name, Component *component)
    {
        if (FindComponent(name))
            throw PunkInvalidArgumentException(string(L"{0} has been already registered").arg(name));
        m_components.push_back(component);
    }

    void ComponentsPoolImpl::UnregisterComponent(Component* component)
    {
        auto it = std::find(m_components.begin(), m_components.end(), component);

        if (it == m_components.end())
            return;                
        m_components.erase(it);
    }
}

#endif  //  USE_SYSTEM_MODULE
