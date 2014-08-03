#ifndef _H_ATTRIBUTES_MODULE_IMPL
#define _H_ATTRIBUTES_MODULE_IMPL

#include <system/module/module.h>

PUNK_ENGINE_BEGIN
namespace Attributes{

	DECLARE_PUNK_GUID(IID_IAttributesModule, "86078DC3-7F92-484C-A0DD-1FF45C7567FD");
	
	class IAttributesManager;

	class IAttributesModule : public System::IModule {
	public:
		virtual Core::Pointer<IAttributesManager> GetAttributeManager() = 0;
	};
}
PUNK_ENGINE_END

#endif	//	_H_ISCENE_MODULE_IMPL
