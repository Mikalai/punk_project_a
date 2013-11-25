#ifndef COMPONENT_INTERFACE_H
#define COMPONENT_INTERFACE_H

#include "config.h"

namespace Punk {
    namespace Engine {
        namespace Core {

            class Object;
            class String;
            class StringList;

            class PUNK_ENGINE_API IComoponent {
            public:
                virtual ~IComoponent() {}
                virtual const String GetName() const = 0;
                virtual const StringList GetServicesList() const = 0;
                virtual Object* Create(const String& name, const String& type, Object** dependency = nullptr) = 0;
                virtual Object* Acquire(const String& name) = 0;
                virtual Object* Acquire(const String& name, const String& type, Object** dependency = nullptr) = 0;
                virtual void Release(const String& name) = 0;
                virtual void Release(Object* instance) = 0;
            };
        }
    }
}
#endif // COMPONENT_INTERFACE_H
