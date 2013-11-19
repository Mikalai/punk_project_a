#ifndef COMPONENTS_POOL_IMPL_H
#define COMPONENTS_POOL_IMPL_H

#include <map>
#include "config.h"
#include "string/string.h"

namespace System
{
    class Component;

    class PUNK_ENGINE_LOCAL ComponentsPoolImpl
    {
    public:
        ~ComponentsPoolImpl();
        void RegisterComponent(const string& name, Component* component);
        void UnregisterComponent(Component* component);
        Component* FindComponent(const string& name);
        void Initialize();
        void Clear();

        std::vector<Component*> m_components;
    };
}

#endif // COMPONENTS_POOL_IMPL_H
