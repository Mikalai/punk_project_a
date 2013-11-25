#include <sstream>
#include "object.h"
#include "string/module.h"

namespace Punk {
    namespace Engine {
        namespace Core {

            unsigned m_id_next = 0;
            Rtti Object::Type("Punk.Engine.Core.Object", typeid(Object).hash_code(), {});

            Object::Object()
                : m_owner{nullptr}
                , m_id(m_id_next++) {
                CREATE_INSTANCE(Object);
            }

            Object::~Object() {
                DESTROY_INSTANCE();
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

            const String Object::ToString() const {
                StringList stream;
                stream << L"[" << String::Convert(GetLocalIndex()) << " " << Type.GetName() << "]";
                return stream.ToString();
            }

            unsigned Object::GetId() const {
                return m_id;
            }

            const String& Object::GetName() const {
                return m_name;
            }

            void Object::SetName(const String& value) {
                m_name = value;
            }

            Object* Object::Clone() const {
                Object* o = new Object();
                String original = GetName();
                String name = original;
                int i = 1;
                while (HasInstance(GetType(), name))
                    name = original + String(L"_{0}").arg(i);
                o->SetName(name);
                return o;
            }

            unsigned Object::Acquire() {
                m_ref_count++;
                return m_ref_count;
            }

            unsigned Object::Release() {
                if (--m_ref_count == 0)
                    delete this;
                return m_ref_count;
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
}
