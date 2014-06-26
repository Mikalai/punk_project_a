#ifndef _H_PUNK_ISHADER
#define _H_PUNK_ISHADER

#include <memory>
#include <config.h>
#include <system/environment.h>
#include <system/filesystem/module.h>
#include <graphics/state/module.h>
#include "shader_type.h"

PUNK_ENGINE_BEGIN
namespace Core { class String; }
namespace Graphics {
	class CoreState;
	class IRenderContext;

	class IShader {
	public:				
		virtual ShaderType GetType() const = 0;
	};
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_ISHADER
