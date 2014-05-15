#include "factory.h"
#include "core_error.h"

PUNK_ENGINE_BEGIN
namespace Core {

	Factory g_factory;

	void Factory::CreateInstance(std::uint64_t type, void** object) {
		auto it = m_creators.find(type);
		if (it == m_creators.end())
			throw Error::CoreException("Creator not found");
		it->second(object);
	}

	void Factory::RegisterCreator(std::uint64_t type, void (*Creator)(void** )) {
		m_creators[type] = Creator;
	}

	void Factory::UnregisterCreator(std::uint64_t type) {
		auto it = m_creators.find(type);
		if (it != m_creators.end())
			m_creators.erase(it);
	}

	extern PUNK_ENGINE_API IFactory* GetFactory() {
		return &g_factory;
	}
}
PUNK_ENGINE_END
