#include <algorithm>
#include <sstream>
#include "object.h"
#include "string/module.h"

namespace Punk {
    namespace Engine {
        namespace Core {

			static Rtti ObjectType{ "Punk.Engine.Core.Object", typeid(Object).hash_code(), {} };

            static std::uint64_t GlobalCounter;
            static Object RootObject;

            Object::Object(Object* parent)
                : m_owner{parent}
                , m_id(GlobalCounter++) {
                if (!m_owner && this != &RootObject)
                    RootObject.Add(this);
            }

            Object::~Object() {
                if (m_owner) {
                    m_owner->Remove(this);
                    m_owner = nullptr;
                }
                while (!m_children.empty()) {
                    Object* child = m_children.back();
                    m_children.pop_back();
                    delete child;
                }
            }

			Rtti* Object::Type() {
				return &ObjectType;
			}

            void Object::SetOwner(Object* owner) {
                m_owner = owner;
            }

            const Object* Object::GetOwner() const {
                return m_owner;
            }

            Object* Object::GetOwner() {
                return m_owner;
            }

            std::uint64_t Object::GetId() const {
                return m_id;
            }

            Object* Object::Clone() const {
                Object* o = new Object();
                for (auto child : m_children) {
                    o->Add(child->Clone());
                }
                return o;
            }

            bool Object::Add(Object* value) {
                if (value == nullptr)
                    return false;

                auto it = std::find(m_children.begin(), m_children.end(), value);
                if (it != m_children.end())
                    return true;

                m_children.push_back(value);
                value->SetOwner(this);

                return true;
            }

            bool Object::Remove(Object* value, bool depth)
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
                        Object* co = As<Object*>(o);
                        if (co)
                        {
                            if (co->Remove(value, depth))
                                return true;
                        }
                    }
                }
                return false;
            }

            bool Object::Remove(int index)
            {
                if (index < 0 || index >= (int)m_children.size())
                    return false;
                return Remove(m_children[index]);
            }


            const Object* Object::Find(int index) const
            {
                return m_children[index];
            }

            Object* Object::Find(int index)
            {
                return const_cast<Object*>(static_cast<const Object*>(this)->Find(index));
            }


            void Bind(Object* parent, Object* child)
            {
                Object* owner = As<Object*>(child->GetOwner());
                if (owner)
                    owner->Remove(child);
                parent->Add(child);
                child->SetOwner(parent);
            }

            const String Object::ToString() const
            {
                StringList stream;
                stream << L"[" << GetType()->GetName() << L"]\n";
                for (auto o : m_children)
                {
                    stream << o->ToString() << L"\n";
                }
                return stream.ToString("");
            }
        }

        //            void SaveObject(Buffer *buffer, const Object *o) {
        //                /*
        //         *  We write type code, as a tag for factory, that should be able
        //         *  to create an object from code. It will not be read from Load.
        //         */
        //                auto id = o->Type.GetId();
        //                buffer->WriteUnsigned32(id);
        //            }

        //            void LoadObject(Buffer*, Object *)
        //            {}
    }
}
