#ifndef _H_IFACTORY
#define _H_IFACTORY

#include <config.h>
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

	struct RegisterCreator {
		RegisterCreator(const Guid& type, void(*F)(void**)) {
			GetFactory()->RegisterCreator(type, F); 
		}
	};

#define PUNK_REGISTER_CREATOR(T, F) Core::RegisterCreator g_##T##creator{T, (F)}

	template<class T>
	T* CreateInstance(const Guid& type) {
		T* object = nullptr;
		GetFactory()->CreateInstance(type, (void**)&object);
		return object;
	}

}
PUNK_ENGINE_END

#endif	//	_H_IFACTORY