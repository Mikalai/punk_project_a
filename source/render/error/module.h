#ifndef _H_RENDER_ERROR_MODULE
#define _H_RENDER_ERROR_MODULE

#include <system/errors/module.h>

PUNK_ENGINE_BEGIN
namespace LowLevelRender {
	namespace Error {
		class PUNK_ENGINE_API RenderException : public System::Error::SystemException {
			using System::Error::SystemException::SystemException;
		};
	}
}
PUNK_ENGINE_END

#endif	//	_H_RENDER_ERROR_MODULE