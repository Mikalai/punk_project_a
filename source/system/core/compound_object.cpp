#include <sstream>
#include <algorithm>
#include "buffer.h"
#include "system/logger/module.h"
#include "compound_object.h"
#include "factory.h"
#include "../engine_objects.h"
#include "meta_class.h"

namespace System
{
    Rtti CompoundObject::Type("System.CompoundObject", typeid(CompoundObject).hash_code(), {&Object::Type});

    CompoundObject::CompoundObject()
    {
        CREATE_INSTANCE(CompoundObject);
    }

    CompoundObject::~CompoundObject()
    {
        for (auto it = m_children.begin(); it != m_children.end(); ++it)
            safe_delete(*it);
        m_children.clear();
        DESTROY_INSTANCE();
    }

    bool CompoundObject::Add(Object* value)
    {
        if (value == nullptr)
        {
            OUT_ERROR("Can't add null object");
            return false;
        }

        auto it = std::find(m_children.begin(), m_children.end(), value);
        if (it != m_children.end())
            return true;

        m_children.push_back(value);
        value->SetOwner(this);

        if (!OnAdd(value))
        {
            OUT_ERROR("OnAdd failed");
            return false;
        }

        return true;
    }

    bool CompoundObject::Remove(Object* value, bool depth)
    {
        if (value == nullptr)
            return false;

        for (auto it = m_children.begin(); it != m_children.end(); ++it)
        {
            if (*it == value)
            {
                m_children.erase(it);
                value->SetOwner(nullptr);
                return true;
            }
        }

        if (depth)
        {
            for (auto o : m_children)
            {
                CompoundObject* co = As<CompoundObject*>(o);
                if (co)
                {
                    if (co->Remove(value, depth))
                        return true;
                }
            }
        }
        return false;
    }

    bool CompoundObject::Remove(int index)
    {
        if (index < 0 || index >= (int)m_children.size())
            return false;
        return Remove(m_children[index]);
    }


    const Object* CompoundObject::Find(int index) const
    {
        return m_children[index];
    }

    Object* CompoundObject::Find(int index)
    {
        return const_cast<Object*>(static_cast<const CompoundObject*>(this)->Find(index));
    }


    void Bind(CompoundObject* parent, Object* child)
    {
        CompoundObject* owner = As<CompoundObject*>(child->GetOwner());
        if (owner)
            owner->Remove(child);
        parent->Add(child);
        child->SetOwner(parent);
    }

    const string CompoundObject::ToString() const
    {
        std::wstringstream stream;
        stream << '[' << GetLocalIndex() << ' ' << Type.GetName() << ']' << std::endl;
        for (auto o : m_children)
        {
            stream << o->ToString() << std::endl;
        }
        return string(stream.str());
    }

    void SaveCompoundObject(Buffer *buffer, const Object *o)
    {
//        SaveObject(buffer, o);
//        const CompoundObject* value = dynamic_cast<const CompoundObject*>(o);
//        unsigned count = value->m_children.size();
//        buffer->WriteUnsigned32(count);
//        for (Object* child : value->m_children)
//        {
//            Factory::Save(buffer, child);
//        }
    }

    void LoadCompoundObject(Buffer *buffer, Object *o)
    {
//        LoadObject(buffer, o);
//        CompoundObject* value = Cast<CompoundObject*>(o);
//        unsigned count{buffer->ReadUnsigned32()};
//        for (auto i = 0u; i != count; ++i)
//        {
//            Object* object = Factory::Load(buffer);
//            value->Add(object);
//        }
    }
}
