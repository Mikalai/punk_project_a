#ifndef H_FACTORY
#define H_FACTORY

#include <map>
#include <config.h>
#include "guid.h"
#include "ifactory.h"

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

}
PUNK_ENGINE_END

#endif	//	H_FACTORY
