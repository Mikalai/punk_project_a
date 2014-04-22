//#include <map>
//#include "component.h"
//#include "components_pool_impl.h"
//#include "components_pool.h"
//
//namespace Punk {
//    namespace Engine {
//        namespace Core {
//
//            ComponentsPool::ComponentsPool()
//                : impl(new ComponentsPoolImpl) {}
//
//            ComponentsPool::~ComponentsPool() {
//                delete impl;
//                impl = nullptr;
//            }
//
//            void ComponentsPool::RegisterComponent(const String &name, Component *component)
//            {
//                impl->RegisterComponent(name, component);
//            }
//
//            void ComponentsPool::UnregisterComponent(Component* component)
//            {
//                impl->UnregisterComponent(component);
//            }
//
//            Component* ComponentsPool::FindComponent(const String &name)
//            {
//                return impl->FindComponent(name);
//            }
//
//            void ComponentsPool::Destroy()
//            {
//                delete m_instance;
//            }
//
//            ComponentsPool* ComponentsPool::Instance()
//            {
//                if (!m_instance)
//                    m_instance = new ComponentsPool;
//                return m_instance;
//            }
//
//            ComponentsPool* ComponentsPool::m_instance;
//
//            void RegisterComponent(Component *value)
//            {
//                ComponentsPool::Instance()->RegisterComponent(value->Execute("get_name"), value);
//            }
//
//            void UnregisterComponent(Component *value)
//            {
//                ComponentsPool::Instance()->UnregisterComponent(value);
//            }
//
//            Component* FindComponent(const String &name)
//            {
//                return ComponentsPool::Instance()->FindComponent(name);
//            }
//        }
//    }
//}
