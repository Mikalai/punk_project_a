#include <iostream>
#include <map>
#include <config.h>
#include "guid.h"
#include "ifactory.h"
#include "core_error.h"

PUNK_ENGINE_BEGIN
namespace Core {

	class PUNK_ENGINE_LOCAL Factory : public IFactory {
	public:
		void CreateInstance(const Guid& type, void** object) override;
		void RegisterCreator(const Guid& type, void(*Creator)(void** object)) override;
		void UnregisterCreator(const Guid& type) override;
	private:
		std::map<const Guid, void(*)(void**)> m_creators;
	};

	static Factory* g_factory;

	void Factory::CreateInstance(const Guid& type, void** object) {
		std::wcout << L"Creating " << (wchar_t*)type.ToString().Data() << std::endl;
		auto it = m_creators.find(type);
		if (it == m_creators.end()) {
			throw Error::CoreException("Creator not found for " + type.ToString());
		}			
		it->second(object);
	}

	void Factory::RegisterCreator(const Guid& type, void(*Creator)(void**)) {
		auto it = m_creators.find(type);
		if (it != m_creators.end()) {
			auto msg = "Create alredy registered for " + type.ToString();
			std::wcout << (wchar_t*)msg.Data() << std::endl;
			throw Error::CoreException(msg);
		}
		m_creators[type] = Creator;
	}

	void Factory::UnregisterCreator(const Guid& type) {
		auto it = m_creators.find(type);
		if (it != m_creators.end())
			m_creators.erase(it);
	}

	extern PUNK_ENGINE_API IFactory* GetFactory() {
		if (!g_factory)
			g_factory = new Factory;
		return g_factory;
	}

	extern PUNK_ENGINE_API void DestroyFactory() {
		if (g_factory)
		{
			delete g_factory;
			g_factory = nullptr;
		}
	}
}
PUNK_ENGINE_END

