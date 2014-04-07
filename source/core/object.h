#ifndef _H_PUNK_SYSTEM_OBJECT
#define _H_PUNK_SYSTEM_OBJECT

#include <vector>
#include <typeinfo>
#include "string/string.h"
#include "core_error.h"
#include "rtti.h"

#define PUNK_OBJECT(T) \
    public: \
    static Core::Rtti Type; \
    virtual Core::Rtti* GetType() const { return &Type; }

PUNK_ENGINE_BEGIN
namespace Core {

    class PUNK_ENGINE_API Object
    {
    public:
        Object(Object* parent = nullptr);
        virtual ~Object();

        void SetOwner(Object* owner);
        const Object* GetOwner() const;
        Object* GetOwner();

        virtual const String ToString() const;
        virtual Object* Clone() const;

        unsigned GetId() const;
        bool Add(Object* object);
        bool Remove(Object* object, bool depth = false);
        bool Remove(int index);
        Object* Find(int index);
        const Object* Find(int index) const;

    public:
        typedef std::vector<Object*> CollectionType;
        typedef CollectionType::iterator iterator;
        typedef CollectionType::const_iterator const_iterator;

        iterator begin() { return m_children.begin(); }
        const_iterator begin() const { return m_children.begin(); }
        iterator end() { return m_children.end(); }
        const_iterator end() const { return m_children.end(); }
        void erase(iterator it) { m_children.erase(it); }
        void clear() { m_children.clear(); }

        PUNK_OBJECT(Object)

    private:
        Object(const Object& o) = delete;
        Object& operator = (const Object& o) = delete;

    private:
        Object* m_owner {nullptr};
        std::uint64_t m_id {0};
        CollectionType m_children;
    };
}
PUNK_ENGINE_END

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
