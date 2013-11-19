#ifdef USE_SYSTEM_MODULE

#include <map>
#include "component.h"
#include "components_pool_impl.h"
#include "components_pool.h"

namespace System
{
    ComponentsPool::ComponentsPool()
        : impl(new ComponentsPoolImpl)
    {}

    ComponentsPool::~ComponentsPool()
    {
        delete impl;
        impl = nullptr;
    }

    void ComponentsPool::RegisterComponent(const string &name, Component *component)
    {
        impl->RegisterComponent(name, component);
    }

    void ComponentsPool::Initialize()
    {
        impl->Initialize();
    }

    void ComponentsPool::Clear()
    {
        impl->Clear();
    }

    void ComponentsPool::UnregisterComponent(Component* component)
    {
        impl->UnregisterComponent(component);
    }

    Component* ComponentsPool::FindComponent(const string &name)
    {
        return impl->FindComponent(name);
    }

    void ComponentsPool::Destroy()
    {
        delete m_instance;
    }

    ComponentsPool* ComponentsPool::Instance()
    {
        if (!m_instance)
            m_instance = new ComponentsPool;
        return m_instance;
    }

    ComponentsPool* ComponentsPool::m_instance;

    void RegisterComponent(Component *value)
    {
        ComponentsPool::Instance()->RegisterComponent(value->GetName(), value);
    }

    void UnregisterComponent(Component *value)
    {
        ComponentsPool::Instance()->UnregisterComponent(value);
    }

    Component* FindComponent(const string &name)
    {
        return ComponentsPool::Instance()->FindComponent(name);
    }

    void InitializeComponents()
    {
        ComponentsPool::Instance()->Initialize();
    }

    void DestroyComponents()
    {
        ComponentsPool::Instance()->Clear();
    }
}

#endif  //  USE_SYSTEM_MODULE
