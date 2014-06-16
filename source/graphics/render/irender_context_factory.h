#ifndef _H_IRENDER_CONTEXT_FACTORY
#define _H_IRENDER_CONTEXT_FACTORY

#include <config.h>
#include <core/iobject.h>
#include "render_context_type.h"

PUNK_ENGINE_BEGIN
namespace Graphics {

	class IRenderContext;
	class IVideoDriver;

	DECLARE_PUNK_GUID(IID_IRenderContextFactory, "CC8F702C-9262-4D10-9D63-1297A7CF571A");

	class IRenderContextFactory : public Core::IObject {
	public:
		virtual IRenderContext* GetOrCreateContext(RenderContextType) = 0;
		virtual void Initialize(IVideoDriver* driver) = 0;
	};

	using IRenderContextFactoryUniquePtr = Core::UniquePtr < IRenderContextFactory > ;
}
PUNK_ENGINE_END

#endif	//	 _H_IRENDER_CONTEXT_FACTORY