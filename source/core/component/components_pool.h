//#ifndef COMPONENTS_POOL_H
//#define COMPONENTS_POOL_H
//
//#include "config.h"
//#include "string/string.h"
//
//PUNK_ENGINE_BEGIN
//namespace Core {
//
//    class ComponentsPoolImpl;
//    class Component;
//
//    class PUNK_ENGINE_API ComponentsPool final
//    {
//    public:
//        ComponentsPool();
//        ComponentsPool(const ComponentsPool&) = delete;
//        ComponentsPool& operator = (const ComponentsPool&) = delete;
//
//        ~ComponentsPool();
//        void RegisterComponent(const String& name, Component* component);
//        void UnregisterComponent(Component* component);
//        Component* FindComponent(const String& name);
//
//        static ComponentsPool* Instance();
//        static void Destroy();
//
//        ComponentsPoolImpl* impl;
//
//    private:
//        static ComponentsPool* m_instance;
//    };
//
//    template<class T>
//    class DeclareComponent
//    {
//    public:
//
//        DeclareComponent() {
//            m_value = new T{};
//            ComponentsPool::Instance()->RegisterComponent(m_value->GetName(), m_value);
//        }
//
//        ~DeclareComponent() {
//            ComponentsPool::Instance()->UnregisterComponent(m_value);
//            delete m_value;
//            m_value = nullptr;
//        }
//
//        T* m_value;
//    };
//
//    //#define REGISTER_COMPONENT(T) Punk::Engine::Core::DeclareComponent<T> Component##T
//
//    //            PUNK_ENGINE_API Component* FindComponent(const String& name);
//
//    //            template<class T>
//    //            T* Create(const String& component, const String& name, const String& service, Object** params = nullptr)
//    //            {
//    //                auto c = FindComponent(component);
//    //                if (c)
//    //                    return dynamic_cast<T*>(c->Create(name, service, params));
//    //                return nullptr;
//    //            }
//
//    //            template<class T>
//    //            T* Acquire(const String& component, const String& name, const String& type, Object** params = nullptr) {
//    //                auto c = FindComponent(component);
//    //                if (c)
//    //                    return dynamic_cast<T*>(c->Acquire(name, type, params));
//    //                return nullptr;
//    //            }
//
//    //            inline void Release(const String& component, const String& object) {
//    //                auto c = FindComponent(component);
//    //                if (c)
//    //                    c->Release(object);
//    //            }
//}
//PUNK_ENGINE_END
//
//#endif // COMPONENTS_POOL_H
