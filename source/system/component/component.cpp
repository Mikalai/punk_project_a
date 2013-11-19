#ifdef USE_SYSTEM_MODULE

#include <iostream>
#include "system/errors/module.h"
#include "component.h"
#include "components_pool.h"

namespace System
{
    void Component::AddDependency(std::initializer_list<string> components)
    {
        m_dependency.insert(m_dependency.begin(), components.begin(), components.end());
    }

    Object* Component::GetService(const string &name)
    {
        if (!m_initialized)
            Initialize();
        return OnGetService(name);
    }
    void Component::Initialize()
    {
        if (m_initialized)
            return;

        if (m_initializing)
            throw PunkException(string(L"Circular dependency detected in {0}").arg(GetName()));

        m_initializing = true;
        for (auto& d : m_dependency)
        {
            if (d.empty())
                continue;

            auto c = FindComponent(d);
            if (!c)
                throw PunkException(string(L"Dependency component '{0}' not found. Can't initialize '{1}'").arg(d).arg(GetName()));
            c->Initialize();
            c->Attach();
        }

        m_initialized = true;
        Attach();
        OnInitialize();
        m_initializing = false;
    }

    const string Component::GetName() const
    {
        return m_name;
    }

    const StringList Component::GetServicesList() const
    {
        return m_services;
    }

    void Component::AddService(const string &service)
    {
        m_services.push_back(service);
    }

    void Component::SetName(const string &name)
    {
        m_name = name;
    }

    void Component::Attach()
    {        
        if (m_ref_count == 1)
        {            
            OnAttach();
        }
        ++m_ref_count;
        std::wcout << "Attaching: " << GetName() << L": " << m_ref_count << std::endl;
    }

    bool Component::Detach()
    {        
        std::wcout << L"Detaching: " << GetName() << L": " << m_ref_count << std::endl;
        --m_ref_count;
        if (m_ref_count == 0) //  TODO: Use interlocked
        {
            OnDetach();
            for (auto& d : m_dependency)
            {
                if (d.empty())
                    continue;

                auto c = FindComponent(d);
                if (c)
                    c->Detach();
            }
            UnregisterComponent(this);
            delete this;
            return true;
        }
        return false;
    }
}

#endif
