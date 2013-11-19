#include <sstream>
#include "meta_class.h"
#include "system/buffer.h"

namespace System
{
    unsigned m_id_next = 0;
    Rtti Object::Type("System.Object", typeid(Object).hash_code(), {});

    Object::Object()
        : m_owner{nullptr}
        , m_id(m_id_next++)        
    {
        CREATE_INSTANCE(Object);
    }

    Object::~Object()
    {
        DESTROY_INSTANCE();
    }

    void Object::SetOwner(Object* owner)
    {
        m_owner = owner;
    }

    const Object* Object::GetOwner() const
    {
        return m_owner;
    }

    Object* Object::GetOwner()
    {
        return m_owner;
    }  

    const string Object::ToString() const
    {
        std::wstringstream stream;
        stream << '[' << GetLocalIndex() << ' ' << Type.GetName() << ']';
        return string(stream.str());
    }

    unsigned Object::GetId() const
    {
        return m_id;
    }

    const string& Object::GetName() const
    {
        return m_name;
    }

    void Object::SetName(const string& value)
    {
        m_name = value;
    }

    Object* Object::Clone() const
    {
        Object* o = new Object();
        string original = GetName();
        string name = original;
        int i = 1;
        while (HasInstance(GetMetaClass(), name))
            name = original + string(L"_{0}").arg(i);
        o->SetName(name);
        return o;
    }

    void SaveObject(Buffer *buffer, const Object *o)
    {
        /*
         *  We write type code, as a tag for factory, that should be able
         *  to create an object from code. It will not be read from Load.
         */
        auto id = o->Type.GetId();
        buffer->WriteUnsigned32(id);
    }

    void LoadObject(Buffer*, Object *)
    {}
}
