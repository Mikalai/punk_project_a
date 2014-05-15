#ifndef H_FACTORY
#define H_FACTORY

#include <map>
#include <config.h>
#include "ifactory.h"

PUNK_ENGINE_BEGIN
namespace Core {

	class PUNK_ENGINE_LOCAL Factory : public IFactory {
	public:
		void CreateInstance(std::uint64_t type, void** object) override;
		void RegisterCreator(std::uint64_t type, void(*Creator)(void** object)) override;
		void UnregisterCreator(std::uint64_t type) override;
	private:
		std::map<std::uint64_t, void (*)(void**)> m_creators;
	};

}
PUNK_ENGINE_END

#endif	//	H_FACTORY
