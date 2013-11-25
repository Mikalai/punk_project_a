#ifndef COMPONENTS_POOL_IMPL_H
#define COMPONENTS_POOL_IMPL_H

#include <map>
#include <vector>
#include "config.h"

namespace Punk {
    namespace Engine {
        namespace Core {

            class String;
            class Component;

            class PUNK_ENGINE_LOCAL ComponentsPoolImpl
            {
            public:
                ~ComponentsPoolImpl();
                void RegisterComponent(const String& name, Component* component);
                void UnregisterComponent(Component* component);
                Component* FindComponent(const String& name);
                void Initialize();
                void Clear();

                std::vector<Component*> m_components;
            };
        }
    }
}

#endif // COMPONENTS_POOL_IMPL_H
