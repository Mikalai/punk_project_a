#ifndef COMPONENTS_POOL_H
#define COMPONENTS_POOL_H

#include "config.h"
#include "string/string.h"

namespace System
{
    class ComponentsPoolImpl;
    class Component;

    class PUNK_ENGINE_API ComponentsPool final
    {
    public:
        ComponentsPool();
        ComponentsPool(const ComponentsPool&) = delete;
        ComponentsPool& operator = (const ComponentsPool&) = delete;

        ~ComponentsPool();
        void RegisterComponent(const string& name, Component* component);
        void UnregisterComponent(Component* component);
        Component* FindComponent(const string& name);
        void Initialize();
        void Clear();

        static ComponentsPool* Instance();
        static void Destroy();

        ComponentsPoolImpl* impl;

    private:
        static ComponentsPool* m_instance;
    };

    template<class T>
    class DeclareComponent
    {
    public:

        DeclareComponent(T* value, std::initializer_list<string> dependency)
            : m_value(value)
        {
            value->AddDependency(dependency);
            RegisterComponent(value);
        }

        ~DeclareComponent()
        {
        }

        T* m_value;
    };

#define REGISTER_COMPONENT(T, value, dependency) System::DeclareComponent<T> instance##T(value, dependency);

    PUNK_ENGINE_API void RegisterComponent(Component* value);
    PUNK_ENGINE_API void UnregisterComponent(Component* value);
    PUNK_ENGINE_API Component*FindComponent(const string& name);
    PUNK_ENGINE_API void InitializeComponents();
    PUNK_ENGINE_API void DestroyComponents();

    template<class T>
    T* GetService(const string& component, const string& service)
    {
        auto c = FindComponent(component);
        if (c)
            return dynamic_cast<T*>(c->GetService(service));
        return nullptr;
    }
}

#endif // COMPONENTS_POOL_H
