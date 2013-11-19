#ifndef PUNK_SYSTEM_RTTI_H
#define PUNK_SYSTEM_RTTI_H

#include "config.h"
#include <vector>
#include "string/string.h"

namespace System
{
    class Buffer;
    class Object;

    class PUNK_ENGINE_API Rtti
    {
    public:
        Rtti(const string& name, unsigned uid, std::initializer_list<const Rtti*> parents);
        ~Rtti();
        const string& GetName() const;
        unsigned GetId() const;
        size_t GetParentsCount() const;
        const Rtti* GetParent(size_t index) const;
        bool IsEqual(const Rtti* value) const;
        bool IsDerived(const Rtti* value) const;
        const string ToString() const;
    private:
        string m_name;
        std::vector<const Rtti*> m_parent;
        unsigned m_id;        
    };
}

#endif // PUNK_SYSTEM_RTTI_H
