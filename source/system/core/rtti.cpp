#include "rtti.h"
#include "../string/string.h"
#include <sstream>

namespace System
{

    Rtti::Rtti(const string &name, unsigned uid, std::initializer_list<const Rtti*> parents)
        : m_name(name)
        , m_parent(parents.begin(), parents.end())
        , m_id(uid)
    {        
    }

    Rtti::~Rtti()
    {}

    const string& Rtti::GetName() const
    {
        return m_name;
    }

    unsigned Rtti::GetId() const
    {
        return m_id;
    }

    size_t Rtti::GetParentsCount() const
    {
        return m_parent.size();
    }

    const Rtti* Rtti::GetParent(size_t index) const
    {
        return m_parent[index];
    }

    bool Rtti::IsEqual(const Rtti* value) const
    {
        return this == value;
    }

    bool IsDerived(const Rtti* parent, const Rtti* value)
    {
        if (value == parent)
            return true;
        for (auto i = 0u; i < parent->GetParentsCount(); ++i)
        {
            if (IsDerived(parent->GetParent(i), value))
                return true;
        }
        return false;
    }

    bool Rtti::IsDerived(const Rtti* value) const
    {        
        return ::System::IsDerived(this, value);
    }

    const string Rtti::ToString() const
    {
        std::wstringstream stream;
        stream << L'[' << m_name << L" (" << m_id << L")";
        if (!m_parent.empty())
        {
        for (auto p : m_parent)
        {
            if (p)
                stream << L" -> " << p->ToString() << L']';
            else
                stream << L']';
        }
        }
        else
        {
            stream << L']';
        }
        return string(stream.str());
    }
}
