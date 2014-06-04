#ifndef _H_IFACTORY
#define _H_IFACTORY

#include <config.h>
#include <initializer_list>
#include <cstdint>

PUNK_ENGINE_BEGIN
namespace Core {
	class IObject;
	class Guid;

	class IFactory {
	public:
		virtual void CreateInstance(const Guid& type, void** object) = 0;
		virtual void RegisterCreator(const Guid& type, void(*Creator)(void** object)) = 0;
		virtual void UnregisterCreator(const Guid& type) = 0;
	};

	extern PUNK_ENGINE_API IFactory* GetFactory();
	extern PUNK_ENGINE_API void DestroyFactory();

	struct RegisterCreator {
		RegisterCreator(const Guid& type, void(*F)(void**)) {
			GetFactory()->RegisterCreator(type, F);
		}
	};

#define PUNK_REGISTER_CREATOR(T, F) Core::RegisterCreator g_##T##creator{T, F}

	template<class T, class I = T>
	T* CreateInstance(const Guid& type) {
		T* object = nullptr;
		GetFactory()->CreateInstance(type, (void**)(I*)&object);
		return object;
	}

	template<class T, class I = T>
	void CreateInstance(void** object) {
		if (!object) {
			throw Core::Error::CoreException(Core::String("Can't create instance, because object '") + typeid(T).name() + "' is null");
		}
		*object = (void*)(I*)(new T{});
	}
}
PUNK_ENGINE_END

#endif	//	_H_IFACTORY