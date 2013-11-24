#include <sstream>
#include <algorithm>
#include "string/module.h"
#include "compound_object.h"
#include "meta_class.h"
#include "rtti.h"

namespace Punk {
    namespace Engine {
        namespace Core {

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
                    return false;

                auto it = std::find(m_children.begin(), m_children.end(), value);
                if (it != m_children.end())
                    return true;

                m_children.push_back(value);
                value->SetOwner(this);

                if (!OnAdd(value))
                    return false;

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

            const String CompoundObject::ToString() const
            {
                StringList stream;
                stream << L"[" << String::Convert(GetLocalIndex()) << L" " << Type.GetName() << L"]\n";
                for (auto o : m_children)
                {
                    stream << o->ToString() << L"\n";
                }
                return stream.ToString();
            }
        }
    }
}
