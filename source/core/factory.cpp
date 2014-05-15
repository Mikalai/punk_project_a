#include "factory.h"
#include "core_error.h"

PUNK_ENGINE_BEGIN
namespace Core {

	Factory g_factory;

	IObject* Factory::CreateInstance(std::uint64_t type) {
		auto it = m_creators.find(type);
		if (it == m_creators.end())
			throw Error::CoreException("Creator not found");
		return it->second();
	}

	void Factory::RegisterCreator(std::uint64_t type, IObject* (*Creator)()) {
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
