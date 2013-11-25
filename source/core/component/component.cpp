#include <algorithm>
#include <set>
#include <list>
#include <vector>
#include <iostream>
#include "core/core_error.h"
#include "core/object.h"
#include "component.h"
#include "components_pool.h"

namespace Punk {
    namespace Engine {
        namespace Core {

            namespace __private {
                struct ComponentImpl {
                    String m_name;
                    StringList m_services;
                    bool m_initialized {false};
                    bool m_initializing {false};
                    unsigned m_ref_count {0};
                    std::set<Object*> m_objects;

                    ComponentImpl(const String& name, const StringList& services)
                        : m_name(name)
                        , m_services(services) {}

                    ~ComponentImpl() {
                    }
                };
            }

            Component::Component(const String& name, const StringList& services)
                : impl(new __private::ComponentImpl(name, services)) {}

            Component::~Component() {
                delete impl;
                impl = nullptr;
            }

            Object* Component::Create(const String& name, const String& type, Object** dependecy) {
                Object* o = OnCreate(name, type, dependecy);
                if (o) {
                    impl->m_objects.insert(o);
                }
                return o;
            }

            Object* Component::Acquire(const String& name) {
                auto it = std::find_if(impl->m_objects.begin(), impl->m_objects.end(),
                             [&name](const Object* o) -> bool { return o->GetName() == name; });
                if (it == impl->m_objects.end())
                    return nullptr;
                (*it)->Acquire();
                return *it;
            }

            Object* Component::Acquire(const String& name, const String& type, Object** dependency) {
                Object* o = Acquire(name);
                if (o)
                    return o;
                return Create(name, type, dependency);
            }

            void Component::Release(const String& name) {
                Object* o = Acquire(name);
                if (o)
                {
                    o->Release();
                    Release(o);
                }
            }

            void Component::Release(Object* instance) {
                if (instance->Release() == 0)
                    impl->m_objects.erase(instance);
            }

            const String Component::GetName() const
            {
                return impl->m_name;
            }

            const StringList Component::GetServicesList() const
            {
                return impl->m_services;
            }
        }
    }
}
