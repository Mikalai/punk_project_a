#ifndef COMPONENT_H
#define COMPONENT_H

#include "config.h"
#include <initializer_list>
#include "string/string_list.h"
#include "component_interface.h"

namespace Punk {
    namespace Engine {
        namespace Core {

            namespace __private {
                struct ComponentImpl;
            }

            class Object;
            class ComponentsPool;

            class PUNK_ENGINE_API Component : public IComoponent
            {
            public:
                Component(const String& name, const StringList& services);
                Component(const Component&) = delete;
                Component& operator = (const Component&) = delete;
                virtual ~Component();

                const String GetName() const override final;
                const StringList GetServicesList() const override final;
                Object* Create(const String& name, const String& type, Object** dependency = nullptr) override final;
                Object* Acquire(const String& name) override final;
                Object* Acquire(const String& name, const String& type, Object** dependency = nullptr) override final;
                virtual void Release(const String& name) override final;
                virtual void Release(Object* instance) override final;

                __private::ComponentImpl* impl {nullptr};

            protected:
                virtual Object* OnCreate(const String& name, const String& type, Object** params = nullptr) { (void)name; (void)type; (void)params; return nullptr; }

                friend class ComponentsPool;
            };
        }
    }
}

#endif // COMPONENT_H
