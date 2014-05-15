#ifndef _H_IFACTORY
#define _H_IFACTORY

#include <config.h>
#include <cstdint>

PUNK_ENGINE_BEGIN
namespace Core {
	class IObject;
	class IFactory {
	public:
		virtual void CreateInstance(std::uint64_t type, void** object) = 0;
		virtual void RegisterCreator(std::uint64_t type, void (*Creator)(void** object)) = 0;
		virtual void UnregisterCreator(std::uint64_t type) = 0;
	};

	extern PUNK_ENGINE_API IFactory* GetFactory();		

	struct RegisterCreator {
		RegisterCreator(std::uint64_t type, void (*F)(void**)) {
			GetFactory()->RegisterCreator(type, F); 
		}
	};

#define PUNK_REGISTER_CREATOR(T, F) Core::RegisterCreator g_##T##creator{typeid(T).hash_code(), (F)}

}
PUNK_ENGINE_END

#endif	//	_H_IFACTORY