//#include <iostream>
//#include <algorithm>
//#include <string/string.h>
//#include "core/core_error.h"
//#include "component.h"
//#include "components_pool_impl.h"
//
//namespace Punk {
//    namespace Engine {
//        namespace Core {
//
//            ComponentsPoolImpl::~ComponentsPoolImpl() {
//                while (!m_components.empty()) {
//                    delete m_components.back();
//                    m_components.pop_back();
//                }
//            }
//
//            Component* ComponentsPoolImpl::FindComponent(const String &name) {
//                auto it = std::find_if(m_components.begin(), m_components.end(),
//                                       [&name](Component* c) -> bool { return c->Execute("get_name") == name; }
//                        );
//                if (it == m_components.end())
//                    return nullptr;
//                return *it;
//            }
//
//            void ComponentsPoolImpl::RegisterComponent(const String &name, Component *component) {
//                if (FindComponent(name))
//                    throw Error::CoreException(String(L"{0} has been already registered").arg(name));
//                m_components.push_back(component);
//            }
//
//            void ComponentsPoolImpl::UnregisterComponent(Component* component) {
//                auto it = std::find(m_components.begin(), m_components.end(), component);
//
//                if (it == m_components.end())
//                    return;
//                m_components.erase(it);
//            }
//        }
//    }
//}
//
