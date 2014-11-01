#include <iostream>
#include <map>
#include <config.h>
#include "ifactory.h"

PUNK_ENGINE_BEGIN
namespace System {

    class PUNK_ENGINE_LOCAL Factory final : public IFactory {
	public:
        void CreateInstance(const Core::Guid& type, void** object) override;
        void RegisterCreator(const Core::String& name, const Core::Guid& type, void(*Creator)(void** object)) override;
        void UnregisterCreator(const Core::Guid& type) override;

		std::uint32_t GetCreatorsCount() const override {
			return (std::uint32_t)m_names.size();
		}

		const Core::String GetCreatorName(std::uint32_t index) const override {
			for (auto& v : m_names) {
				if (index == 0)
					return v.second;
				index--;
			}
			return "";
		}

		const Core::Guid GetCreatorGuid(std::uint32_t index) const override {
			for (auto& v : m_names) {
				if (index == 0)
					return v.first;
				index--;
			}
			return "";
		}

		const Core::Guid GetCreatorGuid(const Core::String name) const override {
			for (auto& v : m_names) {
				if (v.second == name)
					return v.first;
			}
			return Core::Guid{};
		}

	private:
        std::map<const Core::Guid, void(*)(void**)> m_creators;
        std::map<const Core::Guid, Core::String> m_names;
	};

	static Factory* g_factory;

    void Factory::CreateInstance(const Core::Guid& type, void** object) {
		auto it = m_creators.find(type);
		if (it == m_creators.end()) {
            throw Error::SystemException("Creator not found for " + type.ToString());
		}			
        GetDefaultLogger()->Debug(L"Creating " + m_names.at(type) + L" ("  + type.ToString() + L")");
		it->second(object);
	}

    void Factory::RegisterCreator(const Core::String& name, const Core::Guid& type, void(*Creator)(void**)) {
		auto it = m_creators.find(type);
		if (it != m_creators.end()) {
            auto msg = "Creator alredy registered for " + type.ToString();
            GetDefaultLogger()->Error(msg);
            throw Error::SystemException(msg);
		}
		GetDefaultLogger()->Debug("Register creator " + name + "(" + type.ToString() + ")");
        m_names[type] = name;
		m_creators[type] = Creator;
	}

    void Factory::UnregisterCreator(const Core::Guid& type) {
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

