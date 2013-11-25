#ifndef PUNK_SYSTEM_CLASS_BASE_H
#define PUNK_SYSTEM_CLASS_BASE_H

#include "config.h"
#include "string/string.h"

namespace Punk {
    namespace Engine {
        namespace Core {

            class Object;

            struct PUNK_ENGINE_API ClassBase {
                virtual ~ClassBase() {}
                virtual size_t GetInstanceCount() const = 0;
                virtual Object* GetInstance(size_t index) const = 0;
                virtual void Add(Object*) = 0;
                virtual void Remove(Object*) = 0;
            };            
        }
    }
}

#endif // PUNK_SYSTEM_CLASS_BASE_H
