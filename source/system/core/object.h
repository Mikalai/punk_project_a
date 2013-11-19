#ifndef _H_PUNK_SYSTEM_OBJECT
#define _H_PUNK_SYSTEM_OBJECT

#include <typeinfo>
#include "string/string.h"
#include "system/errors/module.h"
#include "meta_class_base.h"
#include "rtti.h"

#define PUNK_OBJECT(TYPE) \
public:\
    virtual System::Rtti* GetType() const { return &Type; }\
    unsigned GetLocalIndex() const { return m_local_index; }\
    void SetLocalIndex(unsigned value) { m_local_index = value; }\
private:\
    unsigned m_local_index {0};\
public:\
    static Rtti Type;

#define CREATE_INSTANCE(TYPE)\
    SetMetaClass(System::Class<TYPE>::Instance());\
    GetMetaClass()->Add(this)

#define DESTROY_INSTANCE() GetMetaClass()->Remove(this);

namespace System
{
    class Buffer;

    class PUNK_ENGINE_API Object
	{
	public:
        Object();
        virtual ~Object();

        void SetOwner(Object* owner);
        const Object* GetOwner() const;
        Object* GetOwner();

        unsigned GetId() const;
        virtual const string ToString() const;        

        const string& GetName() const;
        void SetName(const string& value);


        ClassBase* GetMetaClass() const { return m_meta_class; }
        virtual Object* Clone() const;

    protected:
        void SetMetaClass(ClassBase* value) { m_meta_class = value; }

	private:
        Object(const Object& o) = delete;
        Object& operator = (const Object& o) = delete;

        Object* m_owner {nullptr};
        unsigned m_id {0};        
        string m_name;
        ClassBase* m_meta_class;

        PUNK_OBJECT(Object)
	};    
}

template<class T>
inline T As(System::Object* o)
{
	return dynamic_cast<T>(o);
}

template<class T>
inline T As(const System::Object* o)
{
	return dynamic_cast<T>(o);
}

template<class T, class U>
inline T As(U o)
{
	return dynamic_cast<T>(o);
}

template<class T>
inline bool Is(System::Object* o)
{
	return dynamic_cast<T>(o) != nullptr;
}

template<class T>
inline T Cast(System::Object* o)
{
	T ptr = As<T>(o);
	if (ptr == nullptr && o != nullptr)
        throw System::PunkInvalidCastException(System::string(L"Can't cast from {0} to {1}").arg(typeid(o).name()).arg(typeid(T).name()));
	return ptr;
}

template<class T, class U>
inline T Cast(U* o)
{
	T ptr = As<T>(o);
	if (ptr == nullptr && o != nullptr)
        throw System::PunkInvalidCastException(System::string(L"Can't cast from {0} to {1}").arg(typeid(o).name()).arg(typeid(T).name()));
	return ptr;
}

#define safe_delete(V) {delete (V); (V) = nullptr;}
#define safe_delete_array(V) {delete[] (V); (V) = nullptr;}

#endif	//	_H_PUNK_SYSTEM_OBJECT
