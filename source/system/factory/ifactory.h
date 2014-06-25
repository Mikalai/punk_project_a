#ifndef _H_IFACTORY
#define _H_IFACTORY

#include <config.h>
#include <initializer_list>
#include <cstdint>
#include <typeinfo>
#include <core/iobject.h>
#include <core/guid.h>
#include <system/logger/module.h>
#include <system/errors/module.h>

PUNK_ENGINE_BEGIN
namespace System {

	class IFactory {
	public:
        virtual void CreateInstance(const Core::Guid& type, void** object) = 0;
        virtual void RegisterCreator(const Core::String& name, const Core::Guid& type, void(*Creator)(void** object)) = 0;
        virtual void UnregisterCreator(const Core::Guid& type) = 0;
	};

	extern PUNK_ENGINE_API IFactory* GetFactory();
	extern PUNK_ENGINE_API void DestroyFactory();

    namespace __private {
        struct RegisterCreator {
            RegisterCreator(const Core::String& name, const Core::Guid& type, void(*F)(void**))
                : m_type(type)
                , m_func{F}
            {
                GetFactory()->RegisterCreator(name, m_type, m_func);
            }
            ~RegisterCreator() {
                GetFactory()->UnregisterCreator(m_type);
            }

        private:
            Core::Guid m_type;
            void (*m_func)(void**);
        };
    }

#define PUNK_REGISTER_CREATOR(T, F) static System::__private::RegisterCreator g_##T##creator{#T, T, F}

	template<class I>
    I* CreateInstance(const Core::Guid& type) {
        LOG_FUNCTION_SCOPE
		I* object = nullptr;
		GetFactory()->CreateInstance(type, (void**)(I*)&object);
		return object;
	}

    template<class I>
    std::unique_ptr<I, void (*)(Core::IObject*)> CreateInstancePtr(const Core::Guid& type) {
        LOG_FUNCTION_SCOPE
        I* object = nullptr;
        GetFactory()->CreateInstance(type, (void**)(I*)&object);
        if (!object)
            throw Error::SystemException("Failed to create object of type " + type.ToString());
        return Core::UniquePtr<I>{object, Core::DestroyObject};
    }

	template<class T, class I>
	void CreateInstance(void** object) {
        LOG_FUNCTION_SCOPE
		if (!object) {
			throw Core::Error::CoreException(Core::String("Can't create instance, because object '") + typeid(T).name() + "' is null");
		}
        *object = (void*)(I*)(new T);
	}
}
PUNK_ENGINE_END

#endif	//	_H_IFACTORY
