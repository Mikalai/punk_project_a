#ifndef PUNK_SYSTEM_RTTI_H
#define PUNK_SYSTEM_RTTI_H

#include "config.h"
#include <vector>
#include "string/string.h"

namespace Punk {
    namespace Engine {
        namespace Core {

            class Object;

            class PUNK_ENGINE_API Rtti
            {
            public:
                Rtti(const String& name, unsigned uid, std::initializer_list<const Rtti*> parents);
                ~Rtti();
                const String& GetName() const;
                unsigned GetId() const;
                std::size_t GetParentsCount() const;
                const Rtti* GetParent(std::size_t index) const;
                bool IsEqual(const Rtti* value) const;
                bool IsDerived(const Rtti* value) const;
                const String ToString() const;
            private:
                String m_name;
                std::vector<const Rtti*> m_parent;
                unsigned m_id;
            };
        }
    }
}

#endif // PUNK_SYSTEM_RTTI_H
