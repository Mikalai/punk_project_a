#ifndef _H_PUNK_SYSTEM_OBJECT
#define _H_PUNK_SYSTEM_OBJECT

#include <typeinfo>
#include "string/string.h"
#include "core_error.h"
#include "rtti.h"

#define PUNK_OBJECT(TYPE) \
    public:\
    virtual Punk::Engine::Core::Rtti* GetType() const { return &Type; }\
    unsigned GetLocalIndex() const { return m_local_index; }\
    void SetLocalIndex(unsigned value) { m_local_index = value; }\
    private:\
    unsigned m_local_index {0};\
    public:\
    static Punk::Engine::Core::Rtti Type;

#define CREATE_INSTANCE(TYPE) Type.Add(this)

#define DESTROY_INSTANCE() Type.Remove(this)

namespace Punk {
    namespace Engine {
        namespace Core {

            class PUNK_ENGINE_API Object
            {
            public:
                Object();
                virtual ~Object();

                void SetOwner(Object* owner);
                const Object* GetOwner() const;
                Object* GetOwner();

                unsigned GetId() const;
                virtual const String ToString() const;

                const String& GetName() const;
                void SetName(const String& value);

                virtual Object* Clone() const;

                unsigned Acquire();
                unsigned Release();

            private:
                Object(const Object& o) = delete;
                Object& operator = (const Object& o) = delete;

                Object* m_owner {nullptr};
                unsigned m_id {0};
                unsigned m_ref_count {1};
                String m_name;                

                PUNK_OBJECT(Object)
            };
        }
    }
}

template<class T>
inline T As(Punk::Engine::Core::Object* o)
{
    return dynamic_cast<T>(o);
}

template<class T>
inline T As(const Punk::Engine::Core::Object* o)
{
    return dynamic_cast<T>(o);
}

template<class T, class U>
inline T As(U o)
{
    return dynamic_cast<T>(o);
}

template<class T>
inline bool Is(Punk::Engine::Core::Object* o)
{
    return dynamic_cast<T>(o) != nullptr;
}

template<class T>
inline T Cast(Punk::Engine::Core::Object* o)
{
    T ptr = As<T>(o);
    if (ptr == nullptr && o != nullptr)
        throw Punk::Engine::Core::Error::CoreException(Punk::Engine::Core::String(L"Can't cast from {0} to {1}").arg(typeid(o).name()).arg(typeid(T).name()));
    return ptr;
}

template<class T, class U>
inline T Cast(U* o)
{
    T ptr = As<T>(o);
    if (ptr == nullptr && o != nullptr)
        throw Punk::Engine::Core::Error::CoreException(Punk::Engine::Core::String(L"Can't cast from {0} to {1}").arg(typeid(o).name()).arg(typeid(T).name()));
    return ptr;
}

#define safe_delete(V) {delete (V); (V) = nullptr;}
#define safe_delete_array(V) {delete[] (V); (V) = nullptr;}

#endif	//	_H_PUNK_SYSTEM_OBJECT
