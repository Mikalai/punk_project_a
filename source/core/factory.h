#ifndef H_FACTORY
#define H_FACTORY

#include <map>
#include <config.h>
#include "ifactory.h"

PUNK_ENGINE_BEGIN
namespace Core {

	class PUNK_ENGINE_LOCAL Factory : public IFactory {
	public:
		IObject* CreateInstance(std::uint64_t type) override;
		void RegisterCreator(std::uint64_t type, IObject* (*Creator)()) override;
		void UnregisterCreator(std::uint64_t type) override;
	private:
		std::map<std::uint64_t, IObject* (*)()> m_creators;
	};

}
PUNK_ENGINE_END

#endif	//	H_FACTORY
