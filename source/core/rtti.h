#ifndef PUNK_SYSTEM_RTTI_H
#define PUNK_SYSTEM_RTTI_H

#include <initializer_list>
#include <cstdint>
#include "config.h"

namespace Punk {
    namespace Engine {
        namespace Core {

            namespace __private {
                struct RttiImpl;
            }

            class String;
            class Object;

            class PUNK_ENGINE_API Rtti
            {
            public:
                Rtti(const String& name, std::uint64_t uid, std::initializer_list<const Rtti*> parents);
                ~Rtti();
                const String& GetName() const;
                std::uint64_t GetId() const;
                std::size_t GetParentsCount() const;
                const Rtti* GetParent(std::size_t index) const;
                bool IsEqual(const Rtti* value) const;
                bool IsDerived(const Rtti* value) const;
                const String ToString() const;

                std::size_t GetInstanceCount() const;
                Object* GetInstance(std::size_t index);
                const Object* GetInstance(std::size_t index) const;
                void AddChild(Object* value);
                void Remove(Object* value);

                __private::RttiImpl* impl {nullptr};
            };

            PUNK_ENGINE_API const Object* HasInstance(const Rtti* type, const String& name);
        }
    }
}

#endif // PUNK_SYSTEM_RTTI_H
